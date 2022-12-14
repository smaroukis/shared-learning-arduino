> Source: https://www.worldtimzone.com/res/vi.html

## Cursor movement

-   h - move left
-   j - move down
-   k - move up
-   l - move right
-   w - jump by start of words (punctuation considered words)
-   W - jump by words (spaces separate words)
-   e - jump to end of words (punctuation considered words)
-   E - jump to end of words (no punctuation)
-   b - jump backward by words (punctuation considered words)
-   B - jump backward by words (no punctuation)
-   0 - (zero) start of line
-   ^ - first non-blank character of line
-   $ - end of line
-   G - Go To command (prefix with number - 5G goes to line 5)

**Note:** Prefix a cursor movement command with a number to repeat it. For example, 4j moves down 4 lines.

## Insert Mode - Inserting/Appending text

-   i - start insert mode at cursor
-   I - insert at the beginning of the line
-   a - append after the cursor
-   A - append at the end of the line
-   o - open (append) blank line below current line (no need to press return)
-   O - open blank line above current line
-   ea - append at end of word
-   Esc - exit insert mode

## Editing

-   r - replace a single character (does not use insert mode)
-   J - join line below to the current one
-   cc - change (replace) an entire line
-   cw - change (replace) to the end of word
-   c$ - change (replace) to the end of line
-   s - delete character at cursor and subsitute text
-   S - delete line at cursor and substitute text (same as cc)
-   xp - transpose two letters (delete and paste, technically)
-   u - undo
-   . - repeat last command

## Marking text (visual mode)

-   v - start visual mode, mark lines, then do command (such as y-yank)
-   V - start Linewise visual mode
-   o - move to other end of marked area
-   Ctrl+v - start visual block mode
-   O - move to Other corner of block
-   aw - mark a word
-   ab - a () block (with braces)
-   aB - a {} block (with brackets)
-   ib - inner () block
-   iB - inner {} block
-   Esc - exit visual mode

## Visual commands

-   > - shift right
-   < - shift left
-   y - yank (copy) marked text
-   d - delete marked text
-   ~ - switch case

## Cut and Paste

-   yy - yank (copy) a line
-   2yy - yank 2 lines
-   yw - yank word
-   y$ - yank to end of line
-   p - put (paste) the clipboard after cursor
-   P - put (paste) before cursor
-   dd - delete (cut) a line
-   dw - delete (cut) the current word
-   x - delete (cut) current character

## Exiting

-   :w - write (save) the file, but don't exit
-   :wq - write (save) and quit
-   :q - quit (fails if anything has changed)
-   :q! - quit and throw away changes

## Search/Replace

-   /_pattern_ - search for pattern
-   ?_pattern_ - search backward for pattern
-   n - repeat search in same direction
-   N - repeat search in opposite direction
-   :%s/_old_/_new_/g - replace all _old_ with _new_ throughout file
-   :%s/_old_/_new_/gc - replace all _old_ with _new_ throughout file with confirmations

## Working with multiple files

-   :e _filename_ - Edit a file in a new buffer
-   :bnext (or :bn) - go to next buffer
-   :bprev (of :bp) - go to previous buffer
-   :bd - delete a buffer (close a file)
-   :sp _filename_ - Open a file in a new buffer and split window
-   ctrl+ws - Split windows
-   ctrl+ww - switch between windows
-   ctrl+wq - Quit a window
-   ctrl+wv - Split windows vertically

[Another good vim commands cheatsheet](http://www.fprintf.net/vimCheatSheet.html) and a [vi introduction using the "cheat sheet" method](http://www-105.ibm.com/developerworks/education.nsf/linux-onlinecourse-bytitle/8b6edc18e0ec5fe4862569b5006e5ae1)