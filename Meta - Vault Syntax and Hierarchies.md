parent::[[Meta - Main Page]]

> Note this page is specific to [[Obsidian]] usage, talking about the root level Garden topics.

Hierarchies
- we want to keep our "main" hierarchy clean, so **don't include resources, pinouts, tables** here

General Note Guidelines - Atomic & Hierarchical
- **atomic**: keep most notes small so they can be reused and back-linked to. some notes, that functions as "central/parent nodes", tend to be larger 
- **hierarchical**: since we are using a flat file structure, we still want a way to define a hierarchy, which we are doing using inline Dataview fields and the Breadcrumbs plugin

> [!EXAMPLE]- Tables (`#table`) and Pinouts (`#pinout`)
> Tables, pinouts and other specific resources should have a special format, and tagged as follows (this helps keeps other notes atomic and smaller):
> 
> **Tables**
> - If a table will be used again or referenced, like the [[Table - ASCII Values]], we should put it in its **own atomic note** and then where applicable, **transclude** it in the note where we reference the information (e.g. [[Arduino Variable Types]] references the ASCII table)
> - First, (1) name the page as `Table - <Description>`, then (2) at the end of the page, link to any pages that use it with the syntax `garden-topic:: <page_name>`   and (3) add the `#table` tag so we can quickly find it as needed
