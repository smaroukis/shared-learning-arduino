
parent::[[Meta - Main Page]]

We should focus on portability between different editors (e.g. github, other markdown applications).

Markdown itself is inherently portable. But the standard is actually not well defined, with many applications and websites using their own "flavor". 

## Main Guidelines
- don't use YAML front matter 
- limit use of plugins 
- keep Personal & Project Notes in a Personal Folder

### Personal Folders
- Keep Personal & Project Folders in `Personal Folders/<user>`. 
- Root level pages should be relevant to the knowledge topic being explored - i.e. use a **flat file structure**. 
	- instead of `Electrical Engineering/Microprocessors/Atmetl-AVR.md` just place `Atmel-AVR.md` in the root folder. If you want to include a hierarchy you can put `parent: Microprocessors` in the file text.
- Make sure you have rights to use pictures etc. that you include in your notes since this is hosted publicly. 

## Obsidian Specifics
- [[Meta - Obsidian Markdown Syntax]]
- [[Meta - Useful Obsidian Plugins]]
- [[Meta - Obsidian Specific Guidelines]]

## Guidelines in Development
- [[wikilinks vs. markdown links]]

### **Breaking/Issues**
- sometimes I use embedded-page references in a folded callout, esp. to reference a table, which won't show up for other editors


