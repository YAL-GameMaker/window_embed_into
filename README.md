# window_embed_into
This extension allows you to embed your game window into an unrelated window,
such as GMS2 IDE very specifically (if there are any other Practical Uses, I'm not aware of them).

**Available functions:**

* **window_embed_into_ide() ➜ succeeded?**  
	Inserts your game window into the associated GMS2 IDE window (based on reported project name), returns whether successful.
* **window_embed_into(window_class, window_title) ➜ succeeded?**  
	Inserts your game window into arbitrary window matching the filter, returns whether successful.  
	See [MSDN page for FindWindowW](https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-findwindoww) for class/title remarks.  
	Set either to undefined for NULL use (don't use for filter).  
	Set both to undefined to un-embed the window.
* **window_embed_has_parent() ➜ bool**  
	Returns whether the game window had been embedded
* **window_embed_get_parent_width() ➜ pixel width**  
	Returns width of parent window, desktop width if none
* **window_embed_get_parent_height() ➜ pixel height**  
	Returns height of parent window, desktop height if none

**FAQ**

* **Does this work in GMS1?**  
	[Depends on your definition of "works in GMS1"](https://cdn.discordapp.com/attachments/262926723803381761/654813121491370005/2.png)  
	For real though, you'll want to check how window_embed_into_ide works and match your IDE title (since the game doesn't know IDE license/version to figure that out automatically).  
	If you didn't want this for embedding into GameMaker, then yes, all is well.
* **Does this work with GMEdit?**  
	Apparently not? Maybe with hardware acceleration disabled? Blame Chromium
* **Can you embed some other window into the game window?**  
	That requires more functions and effort. This extension is not about effort.
* **Why can you insert windows into other windows just like that?**  
	You see... on Windows, everything is a window - even the (native) buttons and labels. And desktop manager doesn't really mind - if something is assigned as a child to a parent, it gets drawn inside the parent and catches some events.
