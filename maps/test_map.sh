echo "------------- TEST MAP ERRORS -------------"
../cub3d ./map_error/invalid_car.cub
echo "Expected Result :"
echo "Error"
echo "Invalid caracter in the map"
echo ""

../cub3d ./map_error/invalid_width.cub
echo "Expected Result :"
echo "Error"
echo "Invalid map width"
echo ""

../cub3d ./map_error/line_break_in_map.cub
echo "Expected Result :"
echo "Error"
echo "Line beak in map description"
echo ""

../cub3d ./map_error/no_position_on_map.cub
echo "Expected Result :"
echo "Error"
echo "No player position defined"
echo ""

../cub3d ./map_error/two_position_on_map.cub
echo "Expected Result :"
echo "Error"
echo "Player position already defined"
echo ""

../cub3d ./map_error/zero_bottom.cub
echo "Expected Result :"
echo "Error"
echo "Map is not closed on the south side"
echo ""

../cub3d ./map_error/zero_left.cub
echo "Expected Result :"
echo "Error"
echo "Map is not closed on the west side"
echo ""

../cub3d ./map_error/zero_right.cub
echo "Expected Result :"
echo "Error"
echo "Map is not closed on the east side"
echo ""

../cub3d ./map_error/zero_top.cub
echo "Expected Result :"
echo "Error"
echo "Map is not closed on the north side"
echo ""
echo ""
echo ""






echo "------------- TEST MISSING ELEMENT -------------"
../cub3d ./missing_element_error/no_ceiling_color.cub
echo "Expected Result :"
echo "Error"
echo "No ceiling RGB before map in configuration file"
echo ""

../cub3d ./missing_element_error/no_floor_color.cub
echo "Expected Result :"
echo "Error"
echo "No floor RGB before map in configuration file"
echo ""

../cub3d ./missing_element_error/no_north_texture.cub
echo "Expected Result :"
echo "Error"
echo "No north texture before map in configuration file"
echo ""

../cub3d ./missing_element_error/no_south_texture.cub
echo "Expected Result :"
echo "Error"
echo "No south texture before map in configuration file"
echo ""

../cub3d ./missing_element_error/no_west_texture.cub
echo "Expected Result :"
echo "Error"
echo "No west texture before map in configuration file"
echo ""

../cub3d ./missing_element_error/no_east_texture.cub
echo "Expected Result :"
echo "Error"
echo "No east texture before map in configuration file"
echo ""

../cub3d ./missing_element_error/no_map.cub
echo "Expected Result :"
echo "Error"
echo "No map in configuration file"
echo ""

../cub3d ./missing_element_error/no_resolution.cub
echo "Expected Result :"
echo "Error"
echo "No resolution before map in configuration file"
echo ""

../cub3d ./missing_element_error/no_sprite_texture.cub
echo "Expected Result :"
echo "Error"
echo "No sprite texture before map in configuration file"
echo ""
echo ""
echo ""








echo "------------- TEST OTHERS ERRORS -------------"
../cub3d ./other_error/empty_file.cub
echo "Expected Result :"
echo "Error"
echo "Configuration file is empty"
echo ""

../cub3d ./other_error/nt_a_dot_cub
echo "Expected Result :"
echo "Error"
echo "Configuration file can't be open"
echo ""

../cub3d ./other_error/wrong_line.cub
echo "Expected Result :"
echo "Error"
echo "Invalid line in configuration file"
echo ""
echo ""
echo ""







echo "------------- TEST RESOLUTION ERROR -------------"
../cub3d ./resolution_error/car_after_height_res.cub
echo "Expected Result :"
echo "Error"
echo "Invalid caracter after resolution height"
echo ""

../cub3d ./resolution_error/car_before_width_res.cub
echo "Expected Result :"
echo "Error"
echo "Invalid caracter before resolution width"
echo ""

../cub3d ./resolution_error/car_between_width_and_heigth_res.cub
echo "Expected Result :"
echo "Error"
echo "nInvalid caracter between resolution W and H"
echo ""
echo ""
echo ""






echo "------------- TEST RGB ERROR -------------"
../cub3d ./rgb_color_error/car_after_b_ceiling.cub
echo "Expected Result :"
echo "Error"
echo "Invalid caracter after ceiling RGB"
echo ""

../cub3d ./rgb_color_error/car_after_b_floor.cub
echo "Expected Result :"
echo "Error"
echo "Invalid caracter after floor RGB"
echo ""

../cub3d ./rgb_color_error/car_before_r_ceiling.cub
echo "Expected Result :"
echo "Error"
echo "Invalid caracter before ceiling RED"
echo ""

../cub3d ./rgb_color_error/car_before_r_floor.cub
echo "Expected Result :"
echo "Error"
echo "Invalid caracter before floor RED"
echo ""

../cub3d ./rgb_color_error/car_between_g_and_b_ceiling.cub
echo "Expected Result :"
echo "Error"
echo "Invalid caracter between ceiling GREEN and BLUE"
echo ""

../cub3d ./rgb_color_error/car_between_g_and_b_floor.cub
echo "Expected Result :"
echo "Error"
echo "Invalid caracter between floor GREEN and BLUE"
echo ""

../cub3d ./rgb_color_error/car_between_r_and_g_ceiling.cub
echo "Expected Result :"
echo "Error"
echo "Invalid caracter between ceiling RED and GREEN"
echo ""

../cub3d ./rgb_color_error/car_between_r_and_g_floor.cub
echo "Expected Result :"
echo "Error"
echo "Invalid caracter between floor RED and GREEN"
echo ""



../cub3d ./rgb_color_error/invalid_value_b_ceiling.cub
echo "Expected Result :"
echo "Error"
echo "Value over 255 for ceiling BLUE"
echo ""

../cub3d ./rgb_color_error/invalid_value_b_floor.cub
echo "Expected Result :"
echo "Error"
echo "Value over 255 for floor BLUE"
echo ""


../cub3d ./rgb_color_error/invalid_value_g_ceiling.cub
echo "Expected Result :"
echo "Error"
echo "Value over 255 for ceiling GREEN"
echo ""

../cub3d ./rgb_color_error/invalid_value_g_floor.cub
echo "Expected Result :"
echo "Error"
echo "Value over 255 for floor GREEN"
echo ""

../cub3d ./rgb_color_error/invalid_value_r_ceiling.cub
echo "Expected Result :"
echo "Error"
echo "Value over 255 for ceiling RED"
echo ""

../cub3d ./rgb_color_error/invalid_value_r_floor.cub
echo "Expected Result :"
echo "Error"
echo "Value over 255 for floor RED"
echo ""


../cub3d ./rgb_color_error/negative_value_b_ceiling.cub
echo "Expected Result :"
echo "Error"
echo "Value below 0 for ceiling GREEN"
echo ""

../cub3d ./rgb_color_error/negative_value_b_floor.cub
echo "Expected Result :"
echo "Error"
echo "Value below 0 for floor GREEN"
echo ""


../cub3d ./rgb_color_error/negative_value_g_ceiling.cub
echo "Expected Result :"
echo "Error"
echo "Value below 0 for ceiling BLUE"
echo ""

../cub3d ./rgb_color_error/negative_value_g_floor.cub
echo "Expected Result :"
echo "Error"
echo "Value below 0 for floor BLUE"
echo ""

../cub3d ./rgb_color_error/negative_value_r_ceiling.cub
echo "Expected Result :"
echo "Error"
echo "Value below 0 for ceiling RED"
echo ""

../cub3d ./rgb_color_error/negative_value_r_floor.cub
echo "Expected Result :"
echo "Error"
echo "Value below 0 for floor RED"
echo ""


../cub3d ./rgb_color_error/no_coma_between_g_and_b_ceiling.cub
echo "Expected Result :"
echo "Error"
echo "No coma between ceiling GREEN and BLUE"
echo ""

../cub3d ./rgb_color_error/no_coma_between_g_and_b_floor.cub
echo "Expected Result :"
echo "Error"
echo "No coma between floor GREEN and BLUE"
echo ""

../cub3d ./rgb_color_error/no_coma_between_r_and_g_ceiling.cub
echo "Expected Result :"
echo "Error"
echo "No coma between ceiling RED and GREEN"
echo ""

../cub3d ./rgb_color_error/no_coma_between_r_and_g_floor.cub
echo "Expected Result :"
echo "Error"
echo "No coma between floor RED and GREEN"
echo ""
echo ""
echo ""






echo "------------- TEST SPRITE ERROR -------------"
../cub3d ./sprite_error/invalid_car_sprite_texture.cub
echo "Expected Result :"
echo "Error"
echo "Invalid caracter before sprite texture path"
echo ""

../cub3d ./sprite_error/missing_sprite_texture.cub
echo "Expected Result :"
echo "Error"
echo "Sprite texture file can't be open"
echo ""

../cub3d ./sprite_error/sprite_ext.cub
echo "Expected Result :"
echo "Error"
echo "Invalid sprite texture file extension"
echo ""



echo "------------- TEST TEXTURE ERROR -------------"
../cub3d ./texture_error/invalid_car_north_texture.cub
echo "Expected Result :"
echo "Error"
echo "Invalid caracter before wall texture file path"
echo ""

../cub3d ./texture_error/invalid_car_south_texture.cub
echo "Expected Result :"
echo "Error"
echo "Invalid caracter before wall texture file path"
echo ""

../cub3d ./texture_error/invalid_car_west_texture.cub
echo "Expected Result :"
echo "Error"
echo "Invalid caracter before wall texture file path"
echo ""

../cub3d ./texture_error/invalid_car_east_texture.cub
echo "Expected Result :"
echo "Error"
echo "Invalid caracter before wall texture file path"
echo ""


../cub3d ./texture_error/missing_file_north_texture.cub
echo "Expected Result :"
echo "Error"
echo "Wall texture file can't be open"
echo ""

../cub3d ./texture_error/missing_file_south_texture.cub
echo "Expected Result :"
echo "Error"
echo "Wall texture file can't be open"
echo ""

../cub3d ./texture_error/missing_file_west_texture.cub
echo "Expected Result :"
echo "Error"
echo "Wall texture file can't be open"
echo ""

../cub3d ./texture_error/missing_file_east_texture.cub
echo "Expected Result :"
echo "Error"
echo "Wall texture file can't be open"
echo ""


../cub3d ./texture_error/north_texture_ext.cub
echo "Expected Result :"
echo "Error"
echo "Invalid wall texture file extension"
echo ""

../cub3d ./texture_error/south_texture_ext.cub
echo "Expected Result :"
echo "Error"
echo "Invalid wall texture file extension"
echo ""

../cub3d ./texture_error/west_texture_ext.cub
echo "Expected Result :"
echo "Error"
echo "Invalid wall texture file extension"
echo ""

../cub3d ./texture_error/east_texture_ext.cub
echo "Expected Result :"
echo "Error"
echo "Invalid wall texture file extension"
echo ""




echo "------------- TEST ALREADY DEFINED ERROR -------------"
../cub3d ./already_defined/resolution.cub
echo "Expected Result :"
echo "Error"
echo "Resolution already defined"
echo ""

../cub3d ./already_defined/ceiling_rgb.cub
echo "Expected Result :"
echo "Error"
echo "Ceiling RGB is already defined"
echo ""

../cub3d ./already_defined/floor_rgb.cub
echo "Expected Result :"
echo "Error"
echo "Floor RGB is already defined"
echo ""

../cub3d ./already_defined/north_texture.cub
echo "Expected Result :"
echo "Error"
echo "North texture already defined"
echo ""


../cub3d ./already_defined/south_texture.cub
echo "Expected Result :"
echo "Error"
echo "South texture already defined"
echo ""

../cub3d ./already_defined/west_texture.cub
echo "Expected Result :"
echo "Error"
echo "West texture already defined"
echo ""

../cub3d ./already_defined/east_texture.cub
echo "Expected Result :"
echo "Error"
echo "East texture already defined"
echo ""

../cub3d ./already_defined/sprite_texture.cub
echo "Expected Result :"
echo "Error"
echo "Sprite texture already defined"
echo ""
