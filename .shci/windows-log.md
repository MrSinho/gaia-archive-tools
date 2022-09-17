
# gaia-archive-tools

![windows-badge](windows-status.svg)

## [windows build logs:](https://github.com/mrsinho/shci)

        

Build ran for `1.92s`

---

```bash
choco install -y curl mingw cmake
mingw-get install gcc mingw32-make gdb
```

```bash
Chocolatey v0.11.2
Installing the following packages:
curl;mingw;cmake
By installing, you accept licenses for the packages.
curl v7.80.0 already installed.
 Use --force to reinstall, specify a version to install, or try upgrade.
mingw v11.2.0.07112021 already installed.
 Use --force to reinstall, specify a version to install, or try upgrade.
cmake v3.22.0 already installed.
 Use --force to reinstall, specify a version to install, or try upgrade.

Chocolatey installed 0/3 packages. 
 See the log for details (C:\ProgramData\chocolatey\logs\chocolatey.log).

Warnings:
 - cmake - cmake v3.22.0 already installed.
 Use --force to reinstall, specify a version to install, or try upgrade.
 - curl - curl v7.80.0 already installed.
 Use --force to reinstall, specify a version to install, or try upgrade.
 - mingw - mingw v11.2.0.07112021 already installed.
 Use --force to reinstall, specify a version to install, or try upgrade.

Did you know the proceeds of Pro (and some proceeds from other
 licensed editions) go into bettering the community infrastructure?
 Your support ensures an active community, keeps Chocolatey tip-top,
 plus it nets you some awesome features!
 https://chocolatey.org/compare

```

---

    
```bash
cd gaia-archive-tools && mkdir build && cd build && cmake .. -DGAIA_ARCHIVE_TOOLS_BUILD_EXAMPLES=ON && cmake --build .
```

```bash

```

---

    