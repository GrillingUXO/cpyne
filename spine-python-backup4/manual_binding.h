
#ifndef MANUAL_BINDING_H
#define MANUAL_BINDING_H


// ===== 前置声明（按依赖顺序排列）=====
struct spColor;
struct spFloatArray;
struct spShortArray;
struct spIntArray;
struct spUnsignedShortArray;
struct spArrayFloatArray;
struct spArrayShortArray;
struct spBoneDataArray;
struct spIkConstraintDataArray;
struct spTransformConstraintDataArray;
struct spPathConstraintDataArray;
struct spTrackEntryArray;

struct spAttachment;
struct spVertexAttachment;
struct spRegionAttachment;
struct spMeshAttachment;
struct spPointAttachment;
struct spClippingAttachment;
struct spPathAttachment;
struct spBoundingBoxAttachment;

struct spBoneData;
struct spSlotData;
struct spEventData;
struct spEvent;

struct spTimeline;
struct spCurveTimeline;
struct spBaseTimeline;
struct spColorTimeline;
struct spTwoColorTimeline;
struct spAttachmentTimeline;
struct spEventTimeline;
struct spDrawOrderTimeline;
struct spDeformTimeline;
struct spIkConstraintTimeline;
struct spTransformConstraintTimeline;
struct spPathConstraintPositionTimeline;
struct spPathConstraintSpacingTimeline;
struct spPathConstraintMixTimeline;

struct spAnimation;
struct spBone;
struct spSlot;

struct spPathConstraintData;
struct spPathConstraint;
struct spTransformConstraintData;
struct spTransformConstraint;
struct spIkConstraintData;
struct spIkConstraint;

struct spSkeleton;
struct spAttachmentLoader;
struct spAtlasAttachmentLoader;

struct _Entry;
struct _SkinHashTableEntry;
struct spSkin;
struct _spSkin;

struct spVertexEffect;
struct spJitterVertexEffect;
struct spSwirlVertexEffect;

struct spSkeletonData;
struct spSkeletonJson;
struct spSkeletonBinary;

struct spAnimationStateData;
struct spPolygon;
struct spSkeletonBounds;
struct spTriangulator;
struct spSkeletonClipping;

struct spAnimationState;
struct spTrackEntry;

struct spAtlasPage;
struct spAtlasRegion;
struct spAtlas;

// === 基本类型定义 ===
typedef struct spColor {
    float r, g, b, a;
} spColor;

// === 动态数组类型定义 ===
typedef struct spFloatArray {
    float* items;
    int size;
    int capacity;
} spFloatArray;

typedef struct spShortArray {
    short* items;
    int size;
    int capacity;
} spShortArray;

typedef struct spIntArray {
    int* items;
    int size;
    int capacity;
} spIntArray;

typedef struct spUnsignedShortArray {
    unsigned short* items;
    int size;
    int capacity;
} spUnsignedShortArray;

typedef struct spArrayFloatArray {
    spFloatArray** items;
    int size;
    int capacity;
} spArrayFloatArray;

typedef struct spArrayShortArray {
    spShortArray** items;
    int size;
    int capacity;
} spArrayShortArray;

typedef struct spBoneDataArray {
    struct spBoneData** items;
    int size;
    int capacity;
} spBoneDataArray;

typedef struct spIkConstraintDataArray {
    struct spIkConstraintData** items;
    int size;
    int capacity;
} spIkConstraintDataArray;

typedef struct spTransformConstraintDataArray {
    struct spTransformConstraintData** items;
    int size;
    int capacity;
} spTransformConstraintDataArray;

typedef struct spPathConstraintDataArray {
    struct spPathConstraintData** items;
    int size;
    int capacity;
} spPathConstraintDataArray;

typedef struct spTrackEntryArray {
    struct spTrackEntry** items;
    int size;
    int capacity;
} spTrackEntryArray;

// === 核心结构体定义（按依赖顺序）===
typedef struct spAttachment {
    const char* name;
    int type;
    const void* vtable;
    int refCount;
    struct spAttachmentLoader* attachmentLoader;
} spAttachment;

typedef struct spVertexAttachment {
    spAttachment super;
    int id;
    int bonesCount;
    int* bones;
    int verticesCount;
    float* vertices;
    int worldVerticesLength;
    struct spVertexAttachment* deformAttachment;
} spVertexAttachment;

typedef struct spRegionAttachment {
    spAttachment super;
    const char* path;
    float x, y, scaleX, scaleY, rotation, width, height;
    spColor color;
    void* rendererObject;
    int regionOffsetX, regionOffsetY;
    int regionWidth, regionHeight;
    int regionOriginalWidth, regionOriginalHeight;
    float offset[8];
    float uvs[8];
} spRegionAttachment;

typedef struct spMeshAttachment {
    spVertexAttachment super;
    const char* path;
    float* regionUVs;
    float* uvs;
    int trianglesCount;
    unsigned short* triangles;
    float r, g, b, a;
    int hullLength;
    int worldVerticesLength;
    int edgesCount;
    int* edges;
    int width, height;
    void* rendererObject;
    int regionOffsetX, regionOffsetY;
    int regionWidth, regionHeight;
    int regionOriginalWidth, regionOriginalHeight;
    float regionU, regionV, regionU2, regionV2;
    int regionRotate;
    int regionDegrees;
    struct spMeshAttachment* parentMesh;
} spMeshAttachment;

typedef struct spPointAttachment {
    spAttachment super;
    float x, y, rotation;
    spColor color;
} spPointAttachment;

typedef struct spClippingAttachment {
    spVertexAttachment super;
    struct spSlotData* endSlot;
} spClippingAttachment;

typedef struct spPathAttachment {
    spVertexAttachment super;
    int lengthsLength;
    float* lengths;
    int closed, constantSpeed;
} spPathAttachment;

typedef struct spBoundingBoxAttachment {
    spVertexAttachment super;
} spBoundingBoxAttachment;

typedef struct spBoneData {
    int index;
    const char* name;
    struct spBoneData* parent;
    float length;
    float x, y, rotation, scaleX, scaleY, shearX, shearY;
    int transformMode;
    int skinRequired;
} spBoneData;

typedef struct spSlotData {
    int index;
    const char* name;
    struct spBoneData* boneData;
    const char* attachmentName;
    spColor color;
    spColor* darkColor;
    int blendMode;
} spSlotData;

typedef struct spEventData {
    const char* name;
    int intValue;
    float floatValue;
    const char* stringValue;
    const char* audioPath;
    float volume;
    float balance;
} spEventData;

typedef struct spEvent {
    spEventData* data;
    float time;
    int intValue;
    float floatValue;
    const char* stringValue;
    float volume;
    float balance;
} spEvent;

typedef struct spTimeline {
    int propertyId;
    void (*apply)(void*, float, float, float*, float, float, int, int, void*);
} spTimeline;

typedef struct spCurveTimeline {
    spTimeline super;
    float* curves;
} spCurveTimeline;

typedef struct spBaseTimeline {
    spCurveTimeline super;
    int framesCount;
    float* frames;
    int boneIndex;
} spBaseTimeline;

typedef struct spColorTimeline {
    spCurveTimeline super;
    int framesCount;
    float* frames;
    int slotIndex;
} spColorTimeline;

typedef struct spTwoColorTimeline {
    spCurveTimeline super;
    int framesCount;
    float* frames;
    int slotIndex;
} spTwoColorTimeline;

typedef struct spAttachmentTimeline {
    spTimeline super;
    int framesCount;
    float* frames;
    int slotIndex;
    const char** attachmentNames;
} spAttachmentTimeline;

typedef struct spEventTimeline {
    spTimeline super;
    int framesCount;
    float* frames;
    spEvent** events;
} spEventTimeline;

typedef struct spDrawOrderTimeline {
    spTimeline super;
    int framesCount;
    float* frames;
    const int** drawOrders;
    int slotsCount;
} spDrawOrderTimeline;

typedef struct spDeformTimeline {
    spCurveTimeline super;
    int framesCount;
    float* frames;
    int frameVerticesCount;
    const float** frameVertices;
    int slotIndex;
    spAttachment* attachment;
} spDeformTimeline;

typedef struct spIkConstraintTimeline {
    spCurveTimeline super;
    int framesCount;
    float* frames;
    int ikConstraintIndex;
} spIkConstraintTimeline;

typedef struct spTransformConstraintTimeline {
    spCurveTimeline super;
    int framesCount;
    float* frames;
    int transformConstraintIndex;
} spTransformConstraintTimeline;

typedef struct spPathConstraintPositionTimeline {
    spCurveTimeline super;
    int framesCount;
    float* frames;
    int pathConstraintIndex;
} spPathConstraintPositionTimeline;

typedef struct spPathConstraintSpacingTimeline {
    spCurveTimeline super;
    int framesCount;
    float* frames;
    int pathConstraintIndex;
} spPathConstraintSpacingTimeline;

typedef struct spPathConstraintMixTimeline {
    spCurveTimeline super;
    int framesCount;
    float* frames;
    int pathConstraintIndex;
} spPathConstraintMixTimeline;

typedef struct spAnimation {
    const char* name;
    float duration;
    int timelinesCount;
    spTimeline** timelines;
} spAnimation;

typedef struct spBone {
    spBoneData* data;
    struct spSkeleton* skeleton;
    struct spBone* parent;
    int childrenCount;
    struct spBone** children;
    float x, y, rotation, scaleX, scaleY, shearX, shearY;
    float ax, ay, arotation, ascaleX, ascaleY, ashearX, ashearY;
    int appliedValid;
    float a, b, worldX;
    float c, d, worldY;
    int sorted;
    int active;
} spBone;

typedef struct spSlot {
    spSlotData* data;
    struct spBone* bone;
    spColor color;
    spColor* darkColor;
    spAttachment* attachment;
    int attachmentState;
    int deformCapacity;
    int deformCount;
    float* deform;
} spSlot;

typedef struct spPathConstraintData {
    const char* name;
    int order;
    int skinRequired;
    int bonesCount;
    spBoneData** bones;
    struct spSlotData* target;
    int positionMode;
    int spacingMode;
    int rotateMode;
    float offsetRotation;
    float position, spacing, rotateMix, translateMix;
} spPathConstraintData;

typedef struct spPathConstraint {
    spPathConstraintData* data;
    int bonesCount;
    struct spBone** bones;
    struct spSlot* target;
    float position, spacing, rotateMix, translateMix;
    int spacesCount;
    float* spaces;
    int positionsCount;
    float* positions;
    int worldCount;
    float* world;
    int curvesCount;
    float* curves;
    int lengthsCount;
    float* lengths;
    float segments[10];
    int active;
} spPathConstraint;

typedef struct spTransformConstraintData {
    const char* name;
    int order;
    int skinRequired;
    int bonesCount;
    spBoneData** bones;
    spBoneData* target;
    float rotateMix, translateMix, scaleMix, shearMix;
    float offsetRotation, offsetX, offsetY, offsetScaleX, offsetScaleY, offsetShearY;
    int relative;
    int local;
} spTransformConstraintData;

typedef struct spTransformConstraint {
    spTransformConstraintData* data;
    int bonesCount;
    struct spBone** bones;
    struct spBone* target;
    float rotateMix, translateMix, scaleMix, shearMix;
    int active;
} spTransformConstraint;

typedef struct spIkConstraintData {
    const char* name;
    int order;
    int skinRequired;
    int bonesCount;
    spBoneData** bones;
    spBoneData* target;
    int bendDirection;
    int compress;
    int stretch;
    int uniform;
    float mix;
    float softness;
} spIkConstraintData;

typedef struct spIkConstraint {
    spIkConstraintData* data;
    int bonesCount;
    struct spBone** bones;
    struct spBone* target;
    int bendDirection;
    int compress;
    int stretch;
    float mix;
    float softness;
    int active;
} spIkConstraint;

typedef struct spSkeleton {
    struct spSkeletonData* data;
    int bonesCount;
    struct spBone** bones;
    struct spBone* root;
    int slotsCount;
    struct spSlot** slots;
    struct spSlot** drawOrder;
    int ikConstraintsCount;
    struct spIkConstraint** ikConstraints;
    int transformConstraintsCount;
    struct spTransformConstraint** transformConstraints;
    int pathConstraintsCount;
    struct spPathConstraint** pathConstraints;
    struct spSkin* skin;
    spColor color;
    float time;
    float scaleX, scaleY;
    float x, y;
} spSkeleton;

typedef struct spAttachmentLoader {
    const char* error1;
    const char* error2;
    const void* vtable;
} spAttachmentLoader;

typedef struct spAtlasAttachmentLoader {
    spAttachmentLoader super;
    struct spAtlas* atlas;
} spAtlasAttachmentLoader;

typedef struct _Entry {
    int slotIndex;
    const char* name;
    spAttachment* attachment;
    struct _Entry* next;
} _Entry;

typedef struct _SkinHashTableEntry {
    _Entry* entry;
    struct _SkinHashTableEntry* next;
} _SkinHashTableEntry;

typedef struct spSkin {
    const char* name;
    struct spBoneDataArray* bones;
    struct spIkConstraintDataArray* ikConstraints;
    struct spTransformConstraintDataArray* transformConstraints;
    struct spPathConstraintDataArray* pathConstraints;
} spSkin;

typedef struct _spSkin {
    struct spSkin super; 
    _Entry* entries;
    _SkinHashTableEntry* entriesHashTable[101];
} _spSkin;

typedef struct spVertexEffect {
    void (*begin)(void* effect);
    void (*transform)(void* effect, float* vertex, int stride);
    void (*end)(void* effect);
} spVertexEffect;

typedef struct spJitterVertexEffect {
    spVertexEffect super;
    float jitterX;
    float jitterY;
} spJitterVertexEffect;

typedef struct spSwirlVertexEffect {
    spVertexEffect super;
    float centerX;
    float centerY;
    float radius;
    float angle;
    float worldX;
    float worldY;
} spSwirlVertexEffect;

typedef struct spSkeletonData {
    const char* version;
    const char* hash;
    float x, y, width, height;
    int stringsCount;
    char** strings;
    int bonesCount;
    struct spBoneData** bones;
    int slotsCount;
    struct spSlotData** slots;
    int skinsCount;
    struct spSkin** skins;
    struct spSkin* defaultSkin;
    int eventsCount;
    struct spEventData** events;
    int animationsCount;
    struct spAnimation** animations;
    int ikConstraintsCount;
    struct spIkConstraintData** ikConstraints;
    int transformConstraintsCount;
    struct spTransformConstraintData** transformConstraints;
    int pathConstraintsCount;
    struct spPathConstraintData** pathConstraints;
} spSkeletonData;

typedef struct spSkeletonJson {
    float scale;
    struct spAttachmentLoader* attachmentLoader;
    const char* error;
} spSkeletonJson;

typedef struct spSkeletonBinary {
    float scale;
    struct spAttachmentLoader* attachmentLoader;
    const char* error;
} spSkeletonBinary;

typedef struct spAnimationStateData {
    struct spSkeletonData* skeletonData;
    float defaultMix;
    const void* entries;
} spAnimationStateData;

typedef struct spPolygon {
    float* vertices;
    int count;
    int capacity;
} spPolygon;

typedef struct spSkeletonBounds {
    int count;
    struct spBoundingBoxAttachment** boundingBoxes;
    struct spPolygon** polygons;
    float minX, minY, maxX, maxY;
} spSkeletonBounds;

typedef struct spTriangulator {
    struct spArrayFloatArray* convexPolygons;
    struct spArrayShortArray* convexPolygonsIndices;
    struct spShortArray* indicesArray;
    struct spIntArray* isConcaveArray;
    struct spShortArray* triangles;
    struct spArrayFloatArray* polygonPool;
    struct spArrayShortArray* polygonIndicesPool;
} spTriangulator;

typedef struct spSkeletonClipping {
    struct spTriangulator* triangulator;
    struct spFloatArray* clippingPolygon;
    struct spFloatArray* clipOutput;
    struct spFloatArray* clippedVertices;
    struct spFloatArray* clippedUVs;
    struct spUnsignedShortArray* clippedTriangles;
    struct spFloatArray* scratch;
    struct spClippingAttachment* clipAttachment;
    struct spArrayFloatArray* clippingPolygons;
} spSkeletonClipping;

typedef struct spAnimationState spAnimationState;
typedef struct spTrackEntry spTrackEntry;

typedef void (*spAnimationStateListener)(struct spAnimationState* state, int type, struct spTrackEntry* entry, struct spEvent* event);

struct spTrackEntry {
    struct spAnimation* animation;
    struct spTrackEntry* next;
    struct spTrackEntry* mixingFrom;
    struct spTrackEntry* mixingTo;
    spAnimationStateListener listener;
    int trackIndex;
    int loop;
    int holdPrevious;
    float eventThreshold, attachmentThreshold, drawOrderThreshold;
    float animationStart, animationEnd, animationLast, nextAnimationLast;
    float delay, trackTime, trackLast, nextTrackLast, trackEnd, timeScale;
    float alpha, mixTime, mixDuration, interruptAlpha, totalAlpha;
    int mixBlend;
    struct spIntArray* timelineMode;
    struct spTrackEntryArray* timelineHoldMix;
    float* timelinesRotation;
    int timelinesRotationCount;
    void* rendererObject;
    void* userData;
};

typedef struct spAnimationState {
    struct spAnimationStateData* data;
    // 其他字段...
} spAnimationState;

// === 枚举和回调类型 ===
typedef enum spAttachmentType {
    SP_ATTACHMENT_REGION,
    SP_ATTACHMENT_BOUNDING_BOX,
    SP_ATTACHMENT_MESH,
    SP_ATTACHMENT_LINKED_MESH,
    SP_ATTACHMENT_PATH,
    SP_ATTACHMENT_POINT,
    SP_ATTACHMENT_CLIPPING
} spAttachmentType;

typedef enum spAtlasFormat {
    SP_ATLAS_UNKNOWN_FORMAT,
    SP_ATLAS_ALPHA,
    SP_ATLAS_INTENSITY,
    SP_ATLAS_LUMINANCE_ALPHA,
    SP_ATLAS_RGB565,
    SP_ATLAS_RGBA4444,
    SP_ATLAS_RGB888,
    SP_ATLAS_RGBA8888
} spAtlasFormat;

typedef enum {
    SP_MIX_DIRECTION_IN,
    SP_MIX_DIRECTION_OUT
} spMixDirection;

typedef void (*CreateTextureCallback)(struct spAtlasPage* page, const char* path);
typedef void (*DisposeTextureCallback)(struct spAtlasPage* page);
typedef void (*spTimelineApplyFunc)(void* timeline, float time, float alpha, float* blend, float direction, float mix, int pose, int events, void* skeleton);
typedef void (*spVertexEffectBeginFunc)(void* effect);
typedef void (*spVertexEffectTransformFunc)(void* effect, float* vertex, int stride);
typedef void (*spVertexEffectEndFunc)(void* effect);

// === Atlas 相关结构体 ===
typedef struct spAtlasPage {
    struct spAtlas* atlas;
    const char* name;
    spAtlasFormat format;
    int minFilter, magFilter;
    int uWrap, vWrap;
    void* rendererObject;
    int width, height;
    struct spAtlasPage* next;
} spAtlasPage;

typedef struct spAtlasRegion {
    const char* name;
    int x, y, width, height;
    float u, v, u2, v2;
    int offsetX, offsetY;
    int originalWidth, originalHeight;
    int index;
    int rotate;
    int degrees;
    int flip;
    int* splits;
    int* pads;
    struct spAtlasPage* page;
    struct spAtlasRegion* next;
} spAtlasRegion;

typedef struct spAtlas {
    struct spAtlasRegion* regions;
    int regionsCount;
    struct spAtlasPage* pages;
    int pagesCount;
    void* rendererObject;
    const char* error;
} spAtlas;

// === 函数声明 ===
struct spAtlas* spAtlas_createFromFile(const char* path, void* rendererObject);
void spAtlas_dispose(struct spAtlas* atlas);
void spAtlasPage_set_createTexture(CreateTextureCallback callback);
void spAtlasPage_set_disposeTexture(DisposeTextureCallback callback);
struct spAttachmentLoader* spAtlasAttachmentLoader_create(struct spAtlas* atlas);
void spAttachmentLoader_dispose(struct spAttachmentLoader* loader);
struct spSkeletonJson* spSkeletonJson_create(struct spAtlas* atlas);
struct spSkeletonJson* spSkeletonJson_createWithLoader(struct spAttachmentLoader* attachmentLoader);
void spSkeletonJson_dispose(struct spSkeletonJson* json);
struct spSkeletonData* spSkeletonJson_readSkeletonDataFile(struct spSkeletonJson* json, const char* path);
void spSkeletonJson_setScale(struct spSkeletonJson* json, float scale);
struct spSkeletonBinary* spSkeletonBinary_create(struct spAtlas* atlas);
void spSkeletonBinary_dispose(struct spSkeletonBinary* binary);
struct spSkeletonData* spSkeletonBinary_readSkeletonDataFile(struct spSkeletonBinary* binary, const char* path);
void spSkeletonBinary_setScale(struct spSkeletonBinary* binary, float scale);
struct spSkeleton* spSkeleton_create(struct spSkeletonData* data);
void spSkeleton_dispose(struct spSkeleton* skeleton);
void spSkeleton_update(struct spSkeleton* skeleton, float deltaTime);
void spSkeleton_setSkinByName(struct spSkeleton* skeleton, const char* skinName);
void spSkeleton_setToSetupPose(struct spSkeleton* skeleton);
void spSkeleton_updateWorldTransform(struct spSkeleton* skeleton);
void spSkeleton_setBonesToSetupPose(struct spSkeleton* skeleton);
void spSkeleton_setSlotsToSetupPose(struct spSkeleton* skeleton);
void spSkeleton_setAttachment(struct spSkeleton* skeleton, const char* slotName, const char* attachmentName);
struct spBone* spSkeleton_findBone(struct spSkeleton* skeleton, const char* name);
struct spSlot* spSkeleton_findSlot(struct spSkeleton* skeleton, const char* name);
struct spAttachment* spSkeleton_getAttachmentForSlotName(struct spSkeleton* skeleton, const char* slotName, const char* attachmentName);
struct spAttachment* spSkeleton_getAttachmentForSlotIndex(struct spSkeleton* skeleton, int slotIndex, const char* attachmentName);
struct spAnimationStateData* spAnimationStateData_create(struct spSkeletonData* skeletonData);
void spAnimationStateData_dispose(struct spAnimationStateData* stateData);
struct spAnimationState* spAnimationState_create(struct spAnimationStateData* stateData);
void spAnimationState_dispose(struct spAnimationState* state);
void spAnimationState_update(struct spAnimationState* state, float delta);
void spAnimationState_apply(struct spAnimationState* state, struct spSkeleton* skeleton);
int spAnimationState_setAnimationByName(struct spAnimationState* state, int trackIndex, const char* animationName, int loop);
int spAnimationState_addAnimationByName(struct spAnimationState* state, int trackIndex, const char* animationName, int loop, float delay);
void spAnimationState_setListener(struct spAnimationState* state, spAnimationStateListener listener);
void spAnimationState_setVertexEffect(struct spAnimationState* state, struct spVertexEffect* effect);
struct spAnimation* spSkeletonData_findAnimation(struct spSkeletonData* data, const char* name);
struct spSkin* spSkeletonData_findSkin(struct spSkeletonData* data, const char* name);
void spSkeleton_setSkin(struct spSkeleton* skeleton, struct spSkin* newSkin);
struct spIkConstraint* spSkeleton_findIkConstraint(struct spSkeleton* skeleton, const char* name);
struct spTransformConstraint* spSkeleton_findTransformConstraint(struct spSkeleton* skeleton, const char* name);
struct spPathConstraint* spSkeleton_findPathConstraint(struct spSkeleton* skeleton, const char* name);
struct spRegionAttachment* spRegionAttachment_create(const char* name);
struct spMeshAttachment* spMeshAttachment_create(const char* name);
void spMeshAttachment_updateUVs(struct spMeshAttachment* self);
struct spClippingAttachment* spClippingAttachment_create(const char* name);
struct spVertexEffect* spJitterVertexEffect_create(float jitterX, float jitterY);
void spVertexEffect_dispose(struct spVertexEffect* effect);
void spSkeletonClipping_clipStart(struct spSkeletonClipping* self, struct spSlot* slot, struct spClippingAttachment* clip);
void spSkeletonClipping_clipEnd(struct spSkeletonClipping* self, struct spSlot* slot);
void spSkeletonClipping_clipEnd2(struct spSkeletonClipping* self);
void spRegionAttachment_computeWorldVertices(const struct spRegionAttachment* self, struct spSlot* slot, float* worldVertices, int offset, int stride);
void spMeshAttachment_computeWorldVertices(const struct spMeshAttachment* self, struct spSlot* slot, int start, int count, float* worldVertices, int offset, int stride);
struct spEventData* spEventData_create(const char* name);
void spEventData_dispose(struct spEventData* eventData);

// === 强制导出枚举 ===
static const spAttachmentType _ctypegen_force_enum_export = SP_ATTACHMENT_MESH;

SP_API spAttachmentLoader* spAttachmentLoader_createWithMeshSupport(spAtlas* atlas);

#endif /* MANUAL_BINDING_H */
