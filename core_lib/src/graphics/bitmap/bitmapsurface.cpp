#include "bitmapsurface.h"

#include <QPixmap>
#include <QPainter>
#include <QDebug>
#include <QtMath>
#include <QtConcurrent>

BitmapSurface::BitmapSurface()
{

    Tiles tiles;
    mSurface = Surface(tiles, QRect(0,0,1,1));
}

BitmapSurface::BitmapSurface(const BitmapSurface& pieces) : KeyFrame (pieces),
    mSurface(pieces.mSurface)
{
}

BitmapSurface::~BitmapSurface()
{
}

BitmapSurface* BitmapSurface::clone() const
{
    return new BitmapSurface(*this);
}

void BitmapSurface::loadFile()
{
//    if (mImage == nullptr)
//    {
//        mImage = std::make_shared<QImage>(fileName());
//        mBounds.setSize(mImage->size());
//        mMinBound = false;
//    }
}

void BitmapSurface::unloadFile()
{
//    if (isModified() == false)
//    {
//        mImage.reset();
//    }
}

bool BitmapSurface::isLoaded()
{
    return (!mSurface.tiles.isEmpty());
}


bool BitmapSurface::isTransparent(QImage image)
{
    if (!image.hasAlphaChannel()) {
        image = image.convertToFormat(QImage::Format_ARGB32);
    }

    for (int x = 0 ; x < image.width() ; x++) {
        for (int y = 0 ; y < image.height() ; y++) {
            const QRgb pixelColor = *(reinterpret_cast<const QRgb*>(image.constScanLine(x))+y);

            if (qAlpha(pixelColor) != 0) {
                return false;
            }
        }
    }
    return true;
}

void BitmapSurface::createNewSurfaceFromImage(const QString& path, const QPoint& topLeft)
{
    QImage image(path);
    createNewSurfaceFromImage(image, topLeft);
}

void BitmapSurface::createNewSurfaceFromImage(const QImage& image, const QPoint& topLeft)
{
    float imageWidth = static_cast<float>(image.width());
    float imageHeight = static_cast<float>(image.height());
    float tileWidth = static_cast<float>(TILESIZE.width());
    float tileHeight = static_cast<float>(TILESIZE.height());
    int nbTilesOnWidth = static_cast<int>(ceil(imageWidth / tileWidth));
    int nbTilesOnHeight = static_cast<int>(ceil(imageHeight / tileHeight));

    QPixmap paintTo(TILESIZE);
    mSurface = Surface();
    mSurface.bounds = QRect(topLeft, image.size());

    for (int h=0; h < nbTilesOnHeight; h++) {
        for (int w=0; w < nbTilesOnWidth; w++) {
            paintTo.fill(Qt::transparent);
            const QPoint& idx = QPoint(w, h);
            const QPoint& tilePos = getTilePos(idx);

            const QRect& tileRect = QRect(tilePos, TILESIZE);
            const QImage& tileImage = image.copy(tileRect);

            QPainter painter(&paintTo);
            painter.drawImage(QPoint(), tileImage);
            painter.end();

            if (!isTransparent(tileImage)) {
                mSurface.appendTile(paintTo, topLeft+tilePos);
            }
        }
    }
}

void BitmapSurface::addTileToSurface(const QPixmap& pixmap, const QPoint& pos)
{
    mSurface.appendTile(pixmap, pos);

    extendBoundaries(QRect(pos, pixmap.size()));
    mImageCacheValid = false;
}

void BitmapSurface::appendBitmapSurface(const Surface &surface)
{
    mSurface += surface;
    mImageCacheValid = false;
}

void BitmapSurface::renderSurfaceImage()
{
    if (!mImageCacheValid) {
        mCachedSurface = surfaceAsImage();
        mImageCacheValid = true;
    }
}

void BitmapSurface::extendBoundaries(const QRect& rect)
{
    mSurface.extendBoundaries(rect);
}

void BitmapSurface::paintSurfaceUsing(const QPixmap& inPixmap, const QPoint& newPos)
{
    Surface outSurface;

    QPixmap outPix = QPixmap(TILESIZE);
    outPix.fill(Qt::transparent);

    const QRect& adjustedPixRect = QRect(newPos, inPixmap.size());
    const QList<QPoint>& touchedPoints = touchedTiles(adjustedPixRect);

    // paint input pixmap on tiles
    for (int point = 0; point < touchedPoints.count(); point++) {

        const QPoint& touchedPoint = touchedPoints.at(point);
        QPainter painter(&outPix);
        outPix.fill(Qt::transparent);

        painter.save();
        painter.translate(-touchedPoint);
        painter.drawPixmap(newPos, inPixmap);
        painter.restore();
        painter.end();

        QImage testImage = outPix.toImage();
        if (isTransparent(testImage)) {
            continue;
        }

        outSurface.appendTile(outPix, touchedPoint);
        outSurface.bounds = adjustedPixRect;
    }

    Surface extraSurface;

    // paint new tiles on previous tiles if possible, otherwise
    // prepare to be added to bitmapsurface
    QHashIterator<QPoint, std::shared_ptr<QPixmap>> newTiles(outSurface.tiles);
    while (newTiles.hasNext()) {
        newTiles.next();

        QPixmap newPix = outSurface.pixmapAtPos(newTiles.key());
        const QPoint& newPos = outSurface.posFromPixmap(newTiles.value());
        QPixmap paintToPix = QPixmap(newPix.size());
        paintToPix.fill(Qt::transparent);

        bool noMatch = false;
        QHashIterator<QPoint, std::shared_ptr<QPixmap>> cuTiles(mSurface.tiles);
        while (cuTiles.hasNext())
        {
            cuTiles.next();

            QPixmap& existingPix = mSurface.pixmapAtPos(cuTiles.key());
            const QPoint existingPos = mSurface.posFromPixmap(cuTiles.value());

            if (existingPos == newPos) {
                QPainter painter(&existingPix);
                painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
                painter.drawPixmap(QPoint(), newPix);
                painter.end();
            } else {

                if (mSurface.contains(newPos)) {
                    continue;
                }
                noMatch = true;
            }
        }

        if (noMatch)
        {
            extraSurface.appendTile(newPix, newPos);
            extraSurface.bounds = outSurface.bounds;
            noMatch = false;
        }
    }

    appendBitmapSurface(extraSurface);
}

QList<QPoint> BitmapSurface::scanForSurroundingTiles(const QRect& rect)
{
    QPoint kernel[] = {QPoint(-64,-64),QPoint(0,-64), QPoint(64,-64),
                      QPoint(-64,0), QPoint(0,0), QPoint(64,0),
                      QPoint(-64,64), QPoint(0,64), QPoint(64,64)};

    QList<QPoint> points;
    QList<QPoint> corners;

    corners.append({rect.topLeft(), rect.topRight(), rect.bottomLeft(), rect.bottomRight()});
    for (unsigned int i = 0; i < sizeof(kernel)/sizeof(kernel[0]); i++) {

        for (int p = 0; p < corners.count(); p++) {
            const QPoint& corner = corners[p];
            const QPoint& idx = getTileIndex(corner+kernel[i]);
            const QPoint& pos = getTilePos(idx);
            const QRect& rectToIntersect = getRectForPoint(pos);

            if (rectToIntersect.intersects(rect)) {
                if (points.contains(pos)) {
                    continue;
                }

                points.append(pos);
            }
        }
    }

    return points;
}

QList<QPoint> BitmapSurface::scanForTilesAtSelection(const QRect& rect)
{
    const float& imageWidth = static_cast<float>(rect.width());
    const float& imageHeight = static_cast<float>(rect.height());
    const float& tileWidth = static_cast<float>(TILESIZE.width());
    const float& tileHeight = static_cast<float>(TILESIZE.height());
    const int& nbTilesOnWidth = static_cast<int>(ceil(imageWidth / tileWidth));
    const int& nbTilesOnHeight = static_cast<int>(ceil(imageHeight / tileHeight));

    QList<QPoint> points;

    QList<QPoint> corners;
    const QPoint& cornerOffset = QPoint(TILESIZE.width(), TILESIZE.height());

    corners.append({rect.topLeft(), rect.topRight(), rect.bottomLeft(), rect.bottomRight()});
    for (int h=0; h < nbTilesOnHeight; h++) {
        for (int w=0; w < nbTilesOnWidth; w++) {

            const QPoint& tileIndex = QPoint(TILESIZE.width()*w,TILESIZE.height()*h);
            for (int i = 0; i < corners.count(); i++) {
                QPoint movedPos = getTileIndex(corners[i]-cornerOffset);
                movedPos = getTilePos(movedPos)+tileIndex;

                if (points.contains(movedPos)) {
                    continue;
                }

                if (getRectForPoint(movedPos).intersects(rect)) {
                    points.append(movedPos);
                }
            }
        }
    }
    return points;
}

QList<QPoint> BitmapSurface::touchedTiles(const QRect& rect)
{
    return scanForTilesAtSelection(rect);
}

void BitmapSurface::drawRect(QRect rect, QColor color)
{
    float rectWidth = static_cast<float>(rect.width());
    float rectHeight = static_cast<float>(rect.height());
    float tileWidth = static_cast<float>(TILESIZE.width());
    float tileHeight = static_cast<float>(TILESIZE.height());
    int nbTilesOnWidth = static_cast<int>(ceil(rectWidth / tileWidth));
    int nbTilesOnHeight = static_cast<int>(ceil(rectHeight / tileHeight));

    QPixmap paintTo(TILESIZE);
    mSurface = Surface();
    mSurface.bounds = QRect(rect.topLeft(), rect.size());

    for (int h=0; h < nbTilesOnHeight; h++) {
        for (int w=0; w < nbTilesOnWidth; w++) {
            paintTo.fill(Qt::transparent);
            const QPoint& idx = QPoint(w, h);
            const QPoint& tilePos = getTilePos(idx);

            const QRect& tileRect = QRect(tilePos, TILESIZE);
            QImage colorImage = QImage(rect.size(), QImage::Format_ARGB32_Premultiplied);
            colorImage.fill(color);
            const QImage& tileImage = colorImage.copy(tileRect);

            QPainter painter(&paintTo);
            painter.drawImage(QPoint(), tileImage);
            painter.end();

            mSurface.appendTile(paintTo, tilePos);
        }
    }
}

QFuture<QImage> BitmapSurface::futureSurfaceAsImage()
{
    auto asyncPaint = [this]() {
        return surfaceAsImage();
    };
    return QtConcurrent::run(asyncPaint);
}

QImage BitmapSurface::surfaceAsImage()
{
    QImage paintedImage(mSurface.bounds.size(), QImage::Format_ARGB32_Premultiplied);
    paintedImage.fill(Qt::transparent);

    QPainter painter(&paintedImage);
    painter.translate(-mSurface.topLeft());

    QHashIterator<QPoint, std::shared_ptr<QPixmap>> cuTiles(mSurface.tiles);
    while (cuTiles.hasNext()) {
        cuTiles.next();
        const QPixmap& pix = mSurface.pixmapAtPos(cuTiles.key());
        const QPoint& pos = mSurface.posFromPixmap(cuTiles.value());
        painter.drawPixmap(pos, pix);
    }
    painter.end();

    return paintedImage;
}

void BitmapSurface::eraseSelection(const QPoint pos, QPixmap& pixmap, const QRect selection)
{
    fillSelection(pos, pixmap, Qt::transparent, selection);
}

void BitmapSurface::eraseSelection(const QRect selection)
{
    QHashIterator<QPoint, std::shared_ptr<QPixmap>> cuTiles(mSurface.tiles);
    while (cuTiles.hasNext()) {
        cuTiles.next();

        QPixmap& pixmap = mSurface.pixmapAtPos(cuTiles.key());
        const QPoint& pos = mSurface.posFromPixmap(cuTiles.value());
        eraseSelection(pos, pixmap, selection);
    }
}

void BitmapSurface::fillSelection(const QPoint& pos, QPixmap& pixmap, QColor color, const QRect selection)
{
    QPainter painter(&pixmap);
    painter.translate(-pos);
    painter.setCompositionMode(QPainter::CompositionMode_Source);

    const QRect& intersection = selection.intersected(getRectForPoint(pos, pixmap.size()));
    painter.fillRect(intersection, color);
    painter.end();

}

Surface BitmapSurface::intersectedSurface(const QRect rect)
{
    Surface outSurface;
    QHashIterator<QPoint, std::shared_ptr<QPixmap>> cuTiles(mSurface.tiles);
    while (cuTiles.hasNext())
    {
        cuTiles.next();
        const QPixmap& pix = mSurface.pixmapAtPos(cuTiles.key());
        const QPoint& pos = mSurface.posFromPixmap(cuTiles.value());

        if (getRectForPoint(pos, pix.size()).intersects(rect)) {
            outSurface.appendTile(pix, pos);
            outSurface.bounds = rect;
        }
    }

    return outSurface;
}

QPixmap BitmapSurface::cutSurfaceAsPixmap(const QRect selection)
{
    Q_ASSERT(!selection.isEmpty());

    Surface intersectSurface = intersectedSurface(selection);

    eraseSelection(selection);

    QPixmap paintedImage(selection.size());
    paintedImage.fill(Qt::transparent);

    QPainter painter(&paintedImage);
    painter.translate(-selection.topLeft());

    QHashIterator<QPoint, std::shared_ptr<QPixmap>> interTiles(intersectSurface.tiles);
    while(interTiles.hasNext())
    {
        interTiles.next();
        const QPixmap& pix = intersectSurface.pixmapAtPos(interTiles.key());
        const QPoint& pos = intersectSurface.posFromPixmap(interTiles.value());
        painter.drawPixmap(pos, pix);
    }
    return paintedImage;
}

QPixmap BitmapSurface::copySurfaceAsPixmap(const QRect selection)
{
    Q_ASSERT(!selection.isEmpty());

    const Surface& intersectSurface = intersectedSurface(selection);

    QPixmap paintedImage(selection.size());
    paintedImage.fill(Qt::transparent);

    QPainter painter(&paintedImage);
    painter.translate(-selection.topLeft());
    QHashIterator<QPoint, std::shared_ptr<QPixmap>> interTiles(intersectSurface.tiles);
    while(interTiles.hasNext())
    {
        interTiles.next();
        const QPixmap& pix = intersectSurface.pixmapAtPos(interTiles.key());
        const QPoint& pos = intersectSurface.posFromPixmap(interTiles.value());
        painter.drawPixmap(pos, pix);
    }
    return paintedImage;
}

QList<QPoint> BitmapSurface::tilePositions()
{
    return mSurface.tiles.keys();
}

QList<std::shared_ptr<QPixmap>> BitmapSurface::pixmaps()
{
    return mSurface.tiles.values();
}

void BitmapSurface::clear()
{
    mCachedSurface = QImage();
    mSurface.clear();
}

Status BitmapSurface::writeFile(const QString& filename)
{
    if (mSurface.isEmpty()) {
        QFile f(filename);
        if(f.exists())
        {
            bool b = f.remove();
            return (b) ? Status::OK : Status::FAIL;
        }
        return Status::SAFE;
    }

    if (mSurface.tiles.values().first()) {
        const QImage& image = surfaceAsImage();
        bool b = image.save(filename);
        return (b) ? Status::OK : Status::FAIL;
    }
    return Status::FAIL;
}

const QRect BitmapSurface::getRectForPoint(const QPoint& point, const QSize size)
{
    return QRect(point.x(), point.y(), size.width(), size.height());
}

const QRect BitmapSurface::getRectForPoint(const QPoint& point)
{
    return QRect(point.x(), point.y(), TILESIZE.width(), TILESIZE.height());
}

inline QPoint BitmapSurface::getTilePos(const QPoint& idx)
{
    return QPoint(TILESIZE.width()*idx.x(), TILESIZE.height()*idx.y());
}

inline QPoint BitmapSurface::getTileIndex(const QPoint& pos)
{
    return QPoint(pos.x()/TILESIZE.width(), pos.y()/TILESIZE.height());
}

inline QPointF BitmapSurface::getTileFIndex(const QPoint& pos)
{
    return QPointF((qreal)pos.x()/TILESIZE.width(), (qreal)pos.y()/TILESIZE.height());
}


