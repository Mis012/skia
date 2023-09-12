see README for upstream README

#### Linux build (for packaging)

```
git clone https://github.com/Mis012/skia -b with-patches-applied # https://github.com/mono/skia.git if they ever merge the patches
cd skia
cp build/linux-self-hosted/DEPS DEPS
python3 tools/git-sync-deps
# ${arch} tested with x64 and aarch64
gn gen 'out/linux/${arch}' --args='
    is_official_build=true skia_enable_tools=false
    target_os="linux" target_cpu="${arch}"
    skia_use_icu=false skia_use_sfntly=false skia_use_piex=true
    skia_use_system_harfbuzz=true skia_use_system_expat=true skia_use_system_freetype2=true skia_use_system_libjpeg_turbo=true skia_use_system_libpng=true skia_use_system_libwebp=true skia_use_system_zlib=true
    skia_enable_gpu=true
    extra_cflags=[ "-DSKIA_C_DLL" ]
    linux_soname_version="99.9"' # on alpine -fpermissive was needed; version would be taked from skiasharp tag if packaging upstream
ninja -C 'out/linux/${arch}' 'SkiaSharp'
```
