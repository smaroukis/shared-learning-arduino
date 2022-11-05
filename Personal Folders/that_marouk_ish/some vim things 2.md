also see [Vim Cheatsheet](Vim%20Cheatsheet.md)

**Macros**
- record a macro with `q<key>` where we assign the macro to key `<key>`
- stop recording with `q`
- run the macro with `@<key>` (run `3` times with `3@<key>`)
- e.g. the following will insert a `.` on at the beginning of the next 3 lines
```
qa.jq3@a@@
```