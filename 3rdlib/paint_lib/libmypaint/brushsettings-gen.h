// DO NOT EDIT - autogenerated by generate.py

static MyPaintBrushSettingInfo settings_info_array[] = {
    {"opaque", N_("Opacity"), FALSE, 0.0, 1.0, 1.0, N_("0 means brush is transparent, 1 fully visible\n(also known as alpha or opacity)")},
    {"opaque_multiply", N_("Opacity multiply"), FALSE, 0.0, 0.0, 1.0, N_("This gets multiplied with opaque. You should only change the pressure input of this setting. Use 'opaque' instead to make opacity depend on speed.\nThis setting is responsible to stop painting when there is zero pressure. This is just a convention, the behaviour is identical to 'opaque'.")},
    {"opaque_linearize", N_("Opacity linearize"), TRUE, 0.0, 0.9, 1.0, N_("Correct the nonlinearity introduced by blending multiple dabs on top of each other. This correction should get you a linear (\"natural\") pressure response when pressure is mapped to opaque_multiply, as it is usually done. 0.9 is good for standard strokes, set it smaller if your brush scatters a lot, or higher if you use dabs_per_second.\n0.0 the opaque value above is for the individual dabs\n1.0 the opaque value above is for the final brush stroke, assuming each pixel gets (dabs_per_radius*2) brushdabs on average during a stroke")},
    {"radius_logarithmic", N_("Radius"), FALSE, -2.0, 2.0, 6.0, N_("Basic brush radius (logarithmic)\n 0.7 means 2 pixels\n 3.0 means 20 pixels")}, 
    {"hardness", N_("Hardness"), FALSE, 0.0, 0.8, 1.0, N_("Hard brush-circle borders (setting to zero will draw nothing). To reach the maximum hardness, you need to disable Pixel feather.")},
    {"anti_aliasing", N_("Pixel feather"), FALSE, 0.0, 1.0, 5.0, N_("This setting decreases the hardness when necessary to prevent a pixel staircase effect (aliasing) by making the dab more blurred.\n 0.0 disable (for very strong erasers and pixel brushes)\n 1.0 blur one pixel (good value)\n 5.0 notable blur, thin strokes will disappear")}, 
    {"dabs_per_basic_radius", N_("Dabs per basic radius"), TRUE, 0.0, 0.0, 200.0, N_("How many dabs to draw while the pointer moves a distance of one brush radius (more precise: the base value of the radius)")}, 
    {"dabs_per_actual_radius", N_("Dabs per actual radius"), TRUE, 0.0, 2.0, 200.0, N_("Same as above, but the radius actually drawn is used, which can change dynamically")}, 
    {"dabs_per_second", N_("Dabs per second"), TRUE, 0.0, 0.0, 200.0, N_("Dabs to draw each second, no matter how far the pointer moves")}, 
    {"gridmap_scale", N_("GridMap Scale"), FALSE, -10.0, 0.0, 10.0, N_("Changes the overall scale that the GridMap brush input operates on.  Logarithmic (same scale as brush radius).  A scale of 0 will make the grid 256x256 pixels.")}, 
    {"gridmap_scale_x", N_("GridMap Scale X"), FALSE, 0.0, 1.0, 10.0, N_("Changes the scale that the GridMap brush input operates on- affects X axis only.  Scale 0X-5X.  This allows you to stretch or compress the GridMap pattern.")}, 
    {"gridmap_scale_y", N_("GridMap Scale Y"), FALSE, 0.0, 1.0, 10.0, N_("Changes the scale that the GridMap brush input operates on- affects Y axis only.  Scale 0X-5X.  This allows you to stretch or compress the GridMap pattern.")}, 
    {"radius_by_random", N_("Radius by random"), FALSE, 0.0, 0.0, 1.5, N_("Alter the radius randomly each dab. You can also do this with the by_random input on the radius setting. If you do it here, there are two differences:\n1) the opaque value will be corrected such that a big-radius dabs is more transparent\n2) it will not change the actual radius seen by dabs_per_actual_radius")}, 
    {"speed1_slowness", N_("Fine speed filter"), FALSE, 0.0, 0.04, 0.2, N_("How slow the input fine speed is following the real speed\n0.0 change immediately as your speed changes (not recommended, but try it)")}, 
    {"speed2_slowness", N_("Gross speed filter"), FALSE, 0.0, 0.8, 3.0, N_("Same as 'fine speed filter', but note that the range is different")}, 
    {"speed1_gamma", N_("Fine speed gamma"), TRUE, -8.0, 4.0, 8.0, N_("This changes the reaction of the 'fine speed' input to extreme physical speed. You will see the difference best if 'fine speed' is mapped to the radius.\n-8.0 very fast speed does not increase 'fine speed' much more\n+8.0 very fast speed increases 'fine speed' a lot\nFor very slow speed the opposite happens.")}, 
    {"speed2_gamma", N_("Gross speed gamma"), TRUE, -8.0, 4.0, 8.0, N_("Same as 'fine speed gamma' for gross speed")}, 
    {"offset_by_random", N_("Jitter"), FALSE, 0.0, 0.0, 25.0, N_("Add a random offset to the position where each dab is drawn\n 0.0 disabled\n 1.0 standard deviation is one basic radius away\n<0.0 negative values produce no jitter")}, 
    {"offset_y", N_("Offset Y"), FALSE, -40.0, 0.0, 40.0, N_("Moves the dabs up or down based on canvas coordinates.")}, 
    {"offset_x", N_("Offset X"), FALSE, -40.0, 0.0, 40.0, N_("Moves the dabs left or right based on canvas coordinates.")}, 
    {"offset_angle", N_("Angular Offset: Direction"), FALSE, -40.0, 0.0, 40.0, N_("Follows the stroke direction to offset the dabs to one side.")}, 
    {"offset_angle_asc", N_("Angular Offset: Ascension"), FALSE, -40.0, 0.0, 40.0, N_("Follows the tilt direction to offset the dabs to one side.  Requires Tilt.")}, 
    {"offset_angle_2", N_("Angular Offset Mirrored: Direction"), FALSE, 0.0, 0.0, 40.0, N_("Follows the stroke direction to offset the dabs, but to both sides of the stroke.")}, 
    {"offset_angle_2_asc", N_("Angular Offset Mirrored: Ascension"), FALSE, 0.0, 0.0, 40.0, N_("Follows the tilt direction to offset the dabs, but to both sides of the stroke.  Requires Tilt.")}, 
    {"offset_angle_adj", N_("Angular Offsets Adjustment"), FALSE, -180.0, 0.0, 180.0, N_("Change the Angular Offset Angle from the default, which is 90 degrees.")}, 
    {"offset_multiplier", N_("Offsets Multiplier"), FALSE, -2.0, 0.0, 3.0, N_("Logarithmic multiplier for X, Y, and Angular Offset settings.")}, 
    {"offset_by_speed", N_("Offset by speed"), FALSE, -3.0, 0.0, 3.0, N_("Change position depending on pointer speed\n= 0 disable\n> 0 draw where the pointer moves to\n< 0 draw where the pointer comes from")}, 
    {"offset_by_speed_slowness", N_("Offset by speed filter"), FALSE, 0.0, 1.0, 15.0, N_("How slow the offset goes back to zero when the cursor stops moving")}, 
    {"slow_tracking", N_("Slow position tracking"), TRUE, 0.0, 0.0, 10.0, N_("Slowdown pointer tracking speed. 0 disables it, higher values remove more jitter in cursor movements. Useful for drawing smooth, comic-like outlines.")}, 
    {"slow_tracking_per_dab", N_("Slow tracking per dab"), FALSE, 0.0, 0.0, 10.0, N_("Similar as above but at brushdab level (ignoring how much time has passed if brushdabs do not depend on time)")}, 
    {"tracking_noise", N_("Tracking noise"), TRUE, 0.0, 0.0, 12.0, N_("Add randomness to the mouse pointer; this usually generates many small lines in random directions; maybe try this together with 'slow tracking'")}, 
    {"color_h", N_("Color hue"), TRUE, 0.0, 0.0, 1.0, N_("Color hue")}, 
    {"color_s", N_("Color saturation"), TRUE, -0.5, 0.0, 1.5, N_("Color saturation")}, 
    {"color_v", N_("Color value"), TRUE, -0.5, 0.0, 1.5, N_("Color value (brightness, intensity)")}, 
    {"restore_color", N_("Save color"), TRUE, 0.0, 0.0, 1.0, N_("When selecting a brush, the color can be restored to the color that the brush was saved with.\n 0.0 do not modify the active color when selecting this brush\n 0.5 change active color towards brush color\n 1.0 set the active color to the brush color when selected")}, 
    {"change_color_h", N_("Change color hue"), FALSE, -2.0, 0.0, 2.0, N_("Change color hue.\n-0.1 small clockwise color hue shift\n 0.0 disable\n 0.5 counterclockwise hue shift by 180 degrees")}, 
    {"change_color_l", N_("Change color lightness (HSL)"), FALSE, -2.0, 0.0, 2.0, N_("Change the color lightness using the HSL color model.\n-1.0 blacker\n 0.0 disable\n 1.0 whiter")}, 
    {"change_color_hsl_s", N_("Change color satur. (HSL)"), FALSE, -2.0, 0.0, 2.0, N_("Change the color saturation using the HSL color model.\n-1.0 more grayish\n 0.0 disable\n 1.0 more saturated")}, 
    {"change_color_v", N_("Change color value (HSV)"), FALSE, -2.0, 0.0, 2.0, N_("Change the color value (brightness, intensity) using the HSV color model. HSV changes are applied before HSL.\n-1.0 darker\n 0.0 disable\n 1.0 brigher")}, 
    {"change_color_hsv_s", N_("Change color satur. (HSV)"), FALSE, -2.0, 0.0, 2.0, N_("Change the color saturation using the HSV color model. HSV changes are applied before HSL.\n-1.0 more grayish\n 0.0 disable\n 1.0 more saturated")}, 
    {"smudge", N_("Smudge"), FALSE, 0.0, 0.0, 1.0, N_("Paint with the smudge color instead of the brush color. The smudge color is slowly changed to the color you are painting on.\n 0.0 do not use the smudge color\n 0.5 mix the smudge color with the brush color\n 1.0 use only the smudge color")}, 
    {"smudge_length", N_("Smudge length"), FALSE, 0.0, 0.5, 1.0, N_("This controls how fast the smudge color becomes the color you are painting on.\n0.0 immediately update the smudge color (requires more CPU cycles because of the frequent color checks)\n0.5 change the smudge color steadily towards the canvas color\n1.0 never change the smudge color")}, 
    {"smudge_radius_log", N_("Smudge radius"), FALSE, -1.6, 0.0, 1.6, N_("This modifies the radius of the circle where color is picked up for smudging.\n 0.0 use the brush radius\n-0.7 half the brush radius (fast, but not always intuitive)\n+0.7 twice the brush radius\n+1.6 five times the brush radius (slow performance)")}, 
    {"eraser", N_("Eraser"), FALSE, 0.0, 0.0, 1.0, N_("how much this tool behaves like an eraser\n 0.0 normal painting\n 1.0 standard eraser\n 0.5 pixels go towards 50% transparency")}, 
    {"stroke_threshold", N_("Stroke threshold"), TRUE, 0.0, 0.0, 0.5, N_("How much pressure is needed to start a stroke. This affects the stroke input only. MyPaint does not need a minimum pressure to start drawing.")}, 
    {"stroke_duration_logarithmic", N_("Stroke duration"), FALSE, -1.0, 4.0, 7.0, N_("How far you have to move until the stroke input reaches 1.0. This value is logarithmic (negative values will not invert the process).")}, 
    {"stroke_holdtime", N_("Stroke hold time"), FALSE, 0.0, 0.0, 10.0, N_("This defines how long the stroke input stays at 1.0. After that it will reset to 0.0 and start growing again, even if the stroke is not yet finished.\n2.0 means twice as long as it takes to go from 0.0 to 1.0\n9.9 or higher stands for infinite")}, 
    {"custom_input", N_("Custom input"), FALSE, -5.0, 0.0, 5.0, N_("Set the custom input to this value. If it is slowed down, move it towards this value (see below). The idea is that you make this input depend on a mixture of pressure/speed/whatever, and then make other settings depend on this 'custom input' instead of repeating this combination everywhere you need it.\nIf you make it change 'by random' you can generate a slow (smooth) random input.")}, 
    {"custom_input_slowness", N_("Custom input filter"), FALSE, 0.0, 0.0, 10.0, N_("How slow the custom input actually follows the desired value (the one above). This happens at brushdab level (ignoring how much time has passed, if brushdabs do not depend on time).\n0.0 no slowdown (changes apply instantly)")}, 
    {"elliptical_dab_ratio", N_("Elliptical dab: ratio"), FALSE, 1.0, 1.0, 10.0, N_("Aspect ratio of the dabs; must be >= 1.0, where 1.0 means a perfectly round dab. TODO: linearize? start at 0.0 maybe, or log?")}, 
    {"elliptical_dab_angle", N_("Elliptical dab: angle"), FALSE, 0.0, 90.0, 180.0, N_("Angle by which elliptical dabs are tilted\n 0.0 horizontal dabs\n 45.0 45 degrees, turned clockwise\n 180.0 horizontal again")}, 
    {"direction_filter", N_("Direction filter"), FALSE, 0.0, 2.0, 10.0, N_("A low value will make the direction input adapt more quickly, a high value will make it smoother")}, 
    {"lock_alpha", N_("Lock alpha"), FALSE, 0.0, 0.0, 1.0, N_("Do not modify the alpha channel of the layer (paint only where there is paint already)\n 0.0 normal painting\n 0.5 half of the paint gets applied normally\n 1.0 alpha channel fully locked")}, 
    {"colorize", N_("Colorize"), FALSE, 0.0, 0.0, 1.0, N_("Colorize the target layer, setting its hue and saturation from the active brush color while retaining its value and alpha.")}, 
    {"snap_to_pixel", N_("Snap to pixel"), FALSE, 0.0, 0.0, 1.0, N_("Snap brush dab's center and its radius to pixels. Set this to 1.0 for a thin pixel brush.")}, 
    {"pressure_gain_log", N_("Pressure gain"), TRUE, -1.8, 0.0, 1.8, N_("This changes how hard you have to press. It multiplies tablet pressure by a constant factor.")}, 

};

static MyPaintBrushInputInfo inputs_info_array[] = {
    {"pressure", 0.0, 0.0, 0.4, 1.0, FLT_MAX, N_("Pressure"), N_("The pressure reported by the tablet. Usually between 0.0 and 1.0, but it may get larger when a pressure gain is used. If you use the mouse, it will be 0.5 when a button is pressed and 0.0 otherwise.")}, 
    {"speed1", -FLT_MAX, 0.0, 0.5, 4.0, FLT_MAX, N_("Fine speed"), N_("How fast you currently move. This can change very quickly. Try 'print input values' from the 'help' menu to get a feeling for the range; negative values are rare but possible for very low speed.")}, 
    {"speed2", -FLT_MAX, 0.0, 0.5, 4.0, FLT_MAX, N_("Gross speed"), N_("Same as fine speed, but changes slower. Also look at the 'gross speed filter' setting.")}, 
    {"random", 0.0, 0.0, 0.5, 1.0, 1.0, N_("Random"), N_("Fast random noise, changing at each evaluation. Evenly distributed between 0 and 1.")}, 
    {"stroke", 0.0, 0.0, 0.5, 1.0, 1.0, N_("Stroke"), N_("This input slowly goes from zero to one while you draw a stroke. It can also be configured to jump back to zero periodically while you move. Look at the 'stroke duration' and 'stroke hold time' settings.")}, 
    {"direction", 0.0, 0.0, 0.0, 180.0, 180.0, N_("Direction"), N_("The angle of the stroke, in degrees. The value will stay between 0.0 and 180.0, effectively ignoring turns of 180 degrees.")}, 
    {"direction_angle", 0.0, 0.0, 0.0, 360.0, 360.0, N_("Direction 360"), N_("The angle of the stroke, from 0 to 360 degrees.")}, 
    {"attack_angle", -180.0, -180.0, 0.0, 180.0, 180.0, N_("Attack Angle"), N_("The difference between the angle the stylus is pointing and the angle of its stroke movement on the canvas (degrees). The value will stay between 0.0 and +/-180.0.  An attack angle of 0.0 would indicate the stylus is moving in the same direction that the stylus tip is pointing.  An Attack Angle of 90 would mean the direction is perpendicular to the stylus tip, and 180 would mean the pen is being dragged in the opposite direction that the stylus tip is pointing.")}, 
    {"tilt_declination", 0.0, 0.0, 0.0, 90.0, 90.0, N_("Declination"), N_("Declination of stylus tilt. 0 when stylus is parallel to tablet and 90.0 when it's perpendicular to tablet.")}, 
    {"tilt_ascension", -180.0, -180.0, 0.0, 180.0, 180.0, N_("Ascension"), N_("Right ascension of stylus tilt. 0 when stylus working end points to you, +90 when rotated 90 degrees clockwise, -90 when rotated 90 degrees counterclockwise.")}, 
    {"gridmap_x", 0, 0.0, 0.0, 256.0, 256.0, N_("GridMap X"), N_("The X coordinate on a 256 pixel grid.  This will wrap around 0-256 as the cursor is moved on the X axis.  Similar to stroke.  Can be used to add paper texture by modifying opacity, etc.\nNote the brush size should be considerably smaller than the grid scale for best results.")}, 
    {"gridmap_y", 0, 0.0, 0.0, 256.0, 256.0, N_("GridMap Y"), N_("The Y coordinate on a 256 pixel grid.  This will wrap around 0-256 as the cursor is moved on the Y axis.  Similar to stroke.  Can be used to add paper texture by modifying opacity, etc.\nNote the brush size should be considerably smaller than the grid scale for best results.")}, 
    {"brush_radius", -2.0, -2.0, 0.0, 6.0, 6.0, N_("Base Brush Radius"), N_("The base brush radius of the current brush.  This allows you to change the behavior of a brush as you make it bigger or smaller.\nYou can even cancel-out dab size increase and adjust something else to make a brush bigger.\nTake note of dabs-per-basic radius and dabs-per-actual radius, which behave much differently.")}, 
    {"custom", -FLT_MAX, -10.0, 0.0, 10.0, FLT_MAX, N_("Custom"), N_("This is a user defined input. Look at the 'custom input' setting for details.")}, 

};
