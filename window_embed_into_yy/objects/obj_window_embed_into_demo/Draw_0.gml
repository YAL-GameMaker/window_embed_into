draw_set_font(fnt_window_embed_into_demo);
draw_set_color(c_white);

if (window_embed_has_parent()) {
	draw_text(10, 10, "Help! I'm trapped inside GameMaker!");
} else {
	draw_text(10, 10, "Life has been pretty kind so far.");
}