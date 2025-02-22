/*
 * Copyright 2014 Google Inc.
 * Copyright 2015 Xamarin Inc.
 * Copyright 2017 Microsoft Corporation. All rights reserved.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include "include/core/SkImage.h"
#include "include/gpu/ganesh/SkImageGanesh.h"
#include "include/core/SkPicture.h"

#include "include/c/sk_image.h"

#include "src/c/sk_types_priv.h"

void sk_image_ref(const sk_image_t* cimage) {
    AsImage(cimage)->ref();
}

void sk_image_unref(const sk_image_t* cimage) {
    SkSafeUnref(AsImage(cimage));
}

sk_image_t* sk_image_new_raster_copy(const sk_imageinfo_t* cinfo, const void* pixels, size_t rowBytes) {
    return ToImage(SkImages::RasterFromPixmapCopy(SkPixmap(AsImageInfo(cinfo), pixels, rowBytes)).release());
}

sk_image_t* sk_image_new_raster_copy_with_pixmap(const sk_pixmap_t* pixmap) {
    return ToImage(SkImages::RasterFromPixmapCopy(*AsPixmap(pixmap)).release());
}

sk_image_t* sk_image_new_raster_data(const sk_imageinfo_t* cinfo, sk_data_t* pixels, size_t rowBytes) {
    return ToImage(SkImages::RasterFromData(AsImageInfo(cinfo), sk_ref_sp(AsData(pixels)), rowBytes).release());
}

sk_image_t* sk_image_new_raster(const sk_pixmap_t* pixmap, sk_image_raster_release_proc releaseProc, void* context) {
    return ToImage(SkImages::RasterFromPixmap(*AsPixmap(pixmap), releaseProc, context).release());
}

sk_image_t* sk_image_new_from_bitmap(const sk_bitmap_t* cbitmap) {
    return ToImage(SkImages::RasterFromBitmap(*AsBitmap(cbitmap)).release());
}

sk_image_t* sk_image_new_from_encoded(const sk_data_t* cdata) {
    return ToImage(SkImages::DeferredFromEncodedData(sk_ref_sp(AsData(cdata))).release());
}

sk_image_t* sk_image_new_from_texture(gr_recording_context_t* context, const gr_backendtexture_t* texture, gr_surfaceorigin_t origin, sk_colortype_t colorType, sk_alphatype_t alpha, const sk_colorspace_t* colorSpace, const sk_image_texture_release_proc releaseProc, void* releaseContext) {
    return ToImage(SkImages::BorrowTextureFrom(AsGrRecordingContext(context), *AsGrBackendTexture(texture), (GrSurfaceOrigin)origin, (SkColorType)colorType, (SkAlphaType)alpha, sk_ref_sp(AsColorSpace(colorSpace)), releaseProc, releaseContext).release());
}

sk_image_t* sk_image_new_from_adopted_texture(gr_recording_context_t* context, const gr_backendtexture_t* texture, gr_surfaceorigin_t origin, sk_colortype_t colorType, sk_alphatype_t alpha, const sk_colorspace_t* colorSpace) {
    return ToImage(SkImages::AdoptTextureFrom(AsGrRecordingContext(context), *AsGrBackendTexture(texture), (GrSurfaceOrigin)origin, (SkColorType)colorType, (SkAlphaType)alpha, sk_ref_sp(AsColorSpace(colorSpace))).release());
}

sk_image_t* sk_image_new_from_picture(sk_picture_t* picture, const sk_isize_t* dimensions, const sk_matrix_t* cmatrix, const sk_paint_t* paint, bool useFloatingPointBitDepth, const sk_colorspace_t* colorSpace, const sk_surfaceprops_t* props) {
    SkMatrix m;
    if (cmatrix) {
        m = AsMatrix(cmatrix);
    }
    return ToImage(SkImages::DeferredFromPicture(sk_ref_sp(AsPicture(picture)), *AsISize(dimensions), cmatrix ? &m : nullptr, AsPaint(paint), useFloatingPointBitDepth ? SkImages::BitDepth::kF16 : SkImages::BitDepth::kU8, sk_ref_sp(AsColorSpace(colorSpace)), *AsSurfaceProps(props)).release());
}

int sk_image_get_width(const sk_image_t* cimage) {
    return AsImage(cimage)->width();
}

int sk_image_get_height(const sk_image_t* cimage) {
    return AsImage(cimage)->height();
}

uint32_t sk_image_get_unique_id(const sk_image_t* cimage) {
    return AsImage(cimage)->uniqueID();
}

sk_alphatype_t sk_image_get_alpha_type(const sk_image_t* image) {
    return (sk_alphatype_t)AsImage(image)->alphaType();
}

sk_colortype_t sk_image_get_color_type(const sk_image_t* image) {
    return (sk_colortype_t)AsImage(image)->colorType();
}

sk_colorspace_t* sk_image_get_colorspace(const sk_image_t* image) {
    return ToColorSpace(AsImage(image)->refColorSpace().release());
}

bool sk_image_is_alpha_only(const sk_image_t* image) {
    return AsImage(image)->isAlphaOnly();
}

sk_shader_t* sk_image_make_shader(const sk_image_t* image, sk_shader_tilemode_t tileX, sk_shader_tilemode_t tileY, const sk_sampling_options_t* sampling, const sk_matrix_t* cmatrix) {
    SkMatrix m;
    if (cmatrix) {
        m = AsMatrix(cmatrix);
    }
    return ToShader(AsImage(image)->makeShader((SkTileMode)tileX, (SkTileMode)tileY, *AsSamplingOptions(sampling), cmatrix ? &m : nullptr).release());
}

bool sk_image_peek_pixels(const sk_image_t* image, sk_pixmap_t* pixmap) {
    return AsImage(image)->peekPixels(AsPixmap(pixmap));
}

bool sk_image_is_texture_backed(const sk_image_t* image) {
    return AsImage(image)->isTextureBacked();
}

bool sk_image_is_lazy_generated(const sk_image_t* image) {
    return AsImage(image)->isLazyGenerated();
}

bool sk_image_is_valid(const sk_image_t* image, gr_recording_context_t* context) {
    return AsImage(image)->isValid(AsGrRecordingContext(context));
}

bool sk_image_read_pixels(const sk_image_t* image, const sk_imageinfo_t* dstInfo, void* dstPixels, size_t dstRowBytes, int srcX, int srcY, sk_image_caching_hint_t cachingHint) {
    return AsImage(image)->readPixels(AsImageInfo(dstInfo), dstPixels, dstRowBytes, srcX, srcY, (SkImage::CachingHint)cachingHint);
}

bool sk_image_read_pixels_into_pixmap(const sk_image_t* image, const sk_pixmap_t* dst, int srcX, int srcY, sk_image_caching_hint_t cachingHint) {
    return AsImage(image)->readPixels(*AsPixmap(dst), srcX, srcY, (SkImage::CachingHint)cachingHint);
}

bool sk_image_scale_pixels(const sk_image_t* image, const sk_pixmap_t* dst, const sk_sampling_options_t* sampling, sk_image_caching_hint_t cachingHint) {
    return AsImage(image)->scalePixels(*AsPixmap(dst), *AsSamplingOptions(sampling), (SkImage::CachingHint)cachingHint);
}

sk_data_t* sk_image_ref_encoded(const sk_image_t* cimage) {
    return ToData(AsImage(cimage)->refEncodedData().release());
}

sk_image_t* sk_image_make_subset_raster(const sk_image_t* cimage, const sk_irect_t* subset) {
    return ToImage(AsImage(cimage)->makeSubset(nullptr, *AsIRect(subset)).release());
}

sk_image_t* sk_image_make_subset(const sk_image_t* cimage, gr_direct_context_t* context, const sk_irect_t* subset) {
    return ToImage(AsImage(cimage)->makeSubset(AsGrDirectContext(context), *AsIRect(subset)).release());
}

sk_image_t* sk_image_make_texture_image(const sk_image_t* cimage, gr_direct_context_t* context, bool mipmapped, bool budgeted) {
    return ToImage(SkImages::TextureFromImage(AsGrDirectContext(context), AsImage(cimage), (GrMipMapped)mipmapped, (skgpu::Budgeted)budgeted).release());
}

sk_image_t* sk_image_make_non_texture_image(const sk_image_t* cimage) {
    return ToImage(AsImage(cimage)->makeNonTextureImage().release());
}

sk_image_t* sk_image_make_raster_image(const sk_image_t* cimage) {
    return ToImage(AsImage(cimage)->makeRasterImage().release());
}

sk_image_t* sk_image_make_with_filter_raster(const sk_image_t* cimage, const sk_imagefilter_t* filter, const sk_irect_t* subset, const sk_irect_t* clipBounds, sk_irect_t* outSubset, sk_ipoint_t* outOffset) {
    return ToImage(AsImage(cimage)->makeWithFilter(nullptr, AsImageFilter(filter), *AsIRect(subset), *AsIRect(clipBounds), AsIRect(outSubset), AsIPoint(outOffset)).release());
}

sk_image_t* sk_image_make_with_filter(const sk_image_t* cimage, gr_recording_context_t* context, const sk_imagefilter_t* filter, const sk_irect_t* subset, const sk_irect_t* clipBounds, sk_irect_t* outSubset, sk_ipoint_t* outOffset) {
    return ToImage(AsImage(cimage)->makeWithFilter(AsGrRecordingContext(context), AsImageFilter(filter), *AsIRect(subset), *AsIRect(clipBounds), AsIRect(outSubset), AsIPoint(outOffset)).release());
}
