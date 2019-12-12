#define window_embed_into
/// (className, title)->ok?
var l_c = argument0, l_t = argument1;
var l_f = 0;
if (is_string(l_c)) l_f |= 1; else l_c = "";
if (is_string(l_t)) l_f |= 2; else l_t = "";
return window_embed_into_raw(window_handle(), l_c, l_t, l_f);

#define window_embed_into_ide
/// ()
return(window_embed_into(undefined, game_project_name + " - GameMaker Studio 2")
	|| window_embed_into(undefined, game_project_name + " - GameMaker Studio 2*")
);