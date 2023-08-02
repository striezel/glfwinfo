# Version history of glfwinfo

_(Note: This changelog focuses on the major changes between the different
versions. Therefore, it may not contain all changes. Especially smaller fixes or
improvements may be omitted.)_

## Version 0.2.0 (2023-08-02)

* __[new feature]__
  The available video modes of the monitors are now listed, too. Since this
  listing can get quite long, there is a new command line option to suppress the
  listing of video modes, `--skip-video-modes`. With that option specified the
  output will not contain video modes and basically looks like the output of
  version 0.1.0.

* __[fix]__
  Fix problem where virtual monitor position was not shown, even if no error
  occurred during the position query.

## Version 0.1.0 (2023-08-02)

Initial proof of concept.
