if (window_embed_into_ide()) {
	var w = window_embed_get_parent_width();
	var h = window_embed_get_parent_height();
	window_set_position(
		(w - window_get_width()),
		(h - window_get_height()) div 2
	);
}