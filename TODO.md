# TODO

The purpose of this file is to keep track of all ongoing tasks of the project.<br>
This includes the TODOs for the next version(s), non programming tasks like updating README etc. and
bugfixes as well as new features which are not directly related to the upcoming version(s).<br>
The TODOs of the released versions will be moved to the
[OLD_VERSIONS.md][old_versions-url] file.

---

## Version 1.1.0

- [X] (Optimizations) (C)<br>
    Run through the directory entries only once and update `considered_directories` on the way.

- [ ] Manual argument handling (C)<br>
    Therefore string args will be possible.

- [ ] Code Cleanup (Python)<br>
    Implement data structure as used in the C version.

- [ ] Measure execution times of both versions under static circumstances.<br>
    Show the results in the [README][readme-url] but also this measurement
    code should stay in the codebase as an additional printable information
    for `verbose` (see below).

- [X] Convert TODO to Markdown file

- [X] Move the old version TODOs into the separate [OLD_VERSIONS.md][old_versions-url] file.

### Bugfixes:

- [X] Bugfix for Issue [#10][issue_10-url]
- [X] Bugfix for Issue [#12][issue_12-url]
- [X] Bugfix for Issue [#13][issue_13-url]

### Features:

- [ ] Argument `[Number]`<br>
    A Number can be added to args which tells the program how many directories should be made.<br>
    e.g. `cdir test 10`

- [ ] Argument `-v` changes to `--verbose`<br>
    Displays directories which have the correct formatting.
    Shows occurrences of directories, and their numbering as well.

### Status: `dev`

---

## General

---

## Additional Features

- [ ] Argument `-s`<br>
    CDIR should add numbering at the beginning.
    Will be interesting with argument `-f` (see below).

- [ ] Argument `-f FILE`<br>
    A file can be used for multiple directory creation and configuration.

---

## Additional Bugfixes



<!-- MARKDOWN LINKS & IMAGES -->
[old_versions-url]: https://github.com/TristanBandat/cdir/blob/main/OLD_VERSIONS.md
[readme-url]: https://github.com/TristanBandat/cdir/blob/main/README.md
[issue_10-url]: https://github.com/TristanBandat/cdir/issues/10
[issue_12-url]: https://github.com/TristanBandat/cdir/issues/12
[issue_13-url]: https://github.com/TristanBandat/cdir/issues/13
