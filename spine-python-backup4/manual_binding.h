#ifndef MANUAL_BINDING_H
#define MANUAL_BINDING_H

// === Forward declarations ===
typedef struct spVertexAttachment spVertexAttachment;
typedef struct spAtlasPage spAtlasPage;
typedef struct spAtlasRegion spAtlasRegion;
typedef struct spMeshAttachment spMeshAttachment;

typedef struct spAtlas spAtlas;
typedef struct spAnimationState spAnimationState;
typedef struct spFloatArray spFloatArray;


typedef struct spSkeleton spSkeleton;
typedef struct spSkeletonData spSkeletonData;
typedef struct spSkin spSkin;
typedef struct spSlot spSlot;
typedef struct spSlotData spSlotData;
typedef struct spBone spBone;
typedef struct spBoneData spBoneData;
typedef struct spAttachment spAttachment;
typedef struct spAttachmentLoader spAttachmentLoader;
typedef struct spAttachmentTimeline spAttachmentTimeline;
typedef struct spEvent spEvent;
typedef struct spEventData spEventData;
typedef struct spTimeline spTimeline;
typedef struct spCurveTimeline spCurveTimeline;
typedef struct spVertexEffect spVertexEffect;
typedef struct spJitterVertexEffect spJitterVertexEffect;
typedef struct spSwirlVertexEffect spSwirlVertexEffect;
typedef struct spTransformConstraint spTransformConstraint;
typedef struct spTransformConstraintData spTransformConstraintData;
typedef struct spIkConstraint spIkConstraint;
typedef struct spIkConstraintData spIkConstraintData;
typedef struct spPathConstraint spPathConstraint;
typedef struct spPathConstraintData spPathConstraintData;
typedef struct spRegionAttachment spRegionAttachment;
typedef struct spClippingAttachment spClippingAttachment;
typedef struct spPointAttachment spPointAttachment;
typedef struct spPathAttachment spPathAttachment;
typedef struct spColor spColor;
typedef struct spSkeletonJson spSkeletonJson;
typedef struct spSkeletonBinary spSkeletonBinary;
typedef struct spAnimation spAnimation;
typedef struct spAnimationStateData spAnimationStateData;
typedef struct spTriangulator spTriangulator;
typedef struct spArrayFloatArray spArrayFloatArray;
typedef struct spArrayShortArray spArrayShortArray;
typedef struct spShortArray spShortArray;
typedef struct spIntArray spIntArray;
typedef struct spUnsignedShortArray spUnsignedShortArray;
typedef struct spBoneDataArray spBoneDataArray;
typedef struct spIkConstraintDataArray spIkConstraintDataArray;
typedef struct spTransformConstraintDataArray spTransformConstraintDataArray;
typedef struct spPathConstraintDataArray spPathConstraintDataArray;


// === Callback function pointer typedefs ===
typedef void (*CreateTextureCallback)(spAtlasPage* page, const char* path);
typedef void (*DisposeTextureCallback)(spAtlasPage* page);
typedef void (*spAnimationStateListener)(struct spAnimationState* state, int trackIndex, int eventType, struct spEvent* event, int loopCount);
typedef void (*spTimelineApplyFunc)(void* timeline, float time, float alpha, float* blend, float direction, float mix, int pose, int events, void* skeleton);

// === VertexEffect function pointers ===
typedef void (*spVertexEffectBeginFunc)(void* effect);
typedef void (*spVertexEffectTransformFunc)(void* effect, float* vertex, int stride);
typedef void (*spVertexEffectEndFunc)(void* effect);


typedef struct spAnimation {
    const char* name;
    float duration;

    int timelinesCount;
    struct spTimeline** timelines;
} spAnimation;

typedef struct spCurveTimeline {
    struct spTimeline super;
    float* curves; /* type, x, y, ... */
} spCurveTimeline;

typedef struct spBaseTimeline {
    spCurveTimeline super;
    int framesCount;
    float* frames; /* time, angle, ... for rotate. time, x, y, ... for translate and scale. */
    int boneIndex;
} spBaseTimeline;

typedef struct spColorTimeline {
    spCurveTimeline super;
    int framesCount;
    float* frames; /* time, r, g, b, a, ... */
    int slotIndex;
} spColorTimeline;

typedef struct spTwoColorTimeline {
    spCurveTimeline super;
    int framesCount;
    float* frames; /* time, r, g, b, a, ... */
    int slotIndex;
} spTwoColorTimeline;

typedef struct spAttachmentTimeline {
    struct spTimeline super;
    int framesCount;
    float* frames; /* time, ... */
    int slotIndex;
    const char** attachmentNames;
} spAttachmentTimeline;

typedef struct spEventTimeline {
    struct spTimeline super;
    int framesCount;
    float* frames; /* time, ... */
    struct spEvent** events;
} spEventTimeline;

typedef struct spDrawOrderTimeline {
    struct spTimeline super;
    int framesCount;
    float* frames; /* time, ... */
    const int** drawOrders;
    int slotsCount;
} spDrawOrderTimeline;

typedef struct spDeformTimeline {
    spCurveTimeline super;
    int framesCount;
    float* frames; /* time, ... */
    int frameVerticesCount;
    const float** frameVertices;
    int slotIndex;
    struct spAttachment* attachment;
} spDeformTimeline;

typedef struct spIkConstraintTimeline {
    spCurveTimeline super;
    int framesCount;
    float* frames; /* time, mix, bendDirection, ... */
    int ikConstraintIndex;
} spIkConstraintTimeline;

typedef struct spTransformConstraintTimeline {
    spCurveTimeline super;
    int framesCount;
    float* frames; /* time, rotate mix, translate mix, scale mix, shear mix, ... */
    int transformConstraintIndex;
} spTransformConstraintTimeline;

typedef struct spPathConstraintPositionTimeline {
    spCurveTimeline super;
    int framesCount;
    float* frames; /* time, rotate mix, translate mix, scale mix, shear mix, ... */
    int pathConstraintIndex;
} spPathConstraintPositionTimeline;

typedef struct spPathConstraintSpacingTimeline {
    spCurveTimeline super;
    int framesCount;
    float* frames; /* time, rotate mix, translate mix, scale mix, shear mix, ... */
    int pathConstraintIndex;
} spPathConstraintSpacingTimeline;

typedef struct spPathConstraintMixTimeline {
    spCurveTimeline super;
    int framesCount;
    float* frames; /* time, rotate mix, translate mix, scale mix, shear mix, ... */
    int pathConstraintIndex;
} spPathConstraintMixTimeline;

typedef struct spEventData {
    const char* name;
    int intValue;
    float floatValue;
    const char* stringValue;
    const char* audioPath;
    float volume;
    float balance;
} spEventData;

typedef struct spSlotData {
    int index;
    const char* name;
    struct spBoneData* boneData;
    const char* attachmentName;
    struct spColor color;
    struct spColor* darkColor;
    int blendMode; /* spBlendMode enum */
} spSlotData;

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

typedef struct spPathAttachment {
    struct spVertexAttachment super;
    int lengthsLength;
    float* lengths;
    int closed; /* bool */
    int constantSpeed; /* bool */
} spPathAttachment;

typedef struct spPointAttachment {
    struct spAttachment super;
    float x, y, rotation;
    struct spColor color;
} spPointAttachment;

typedef struct spEvent {
    spEventData* data;
    float time;
    int intValue;
    float floatValue;
    const char* stringValue;
    float volume;
    float balance;
} spEvent;

typedef struct spClippingAttachment {
    struct spVertexAttachment super;
    spSlotData* endSlot;
} spClippingAttachment;

typedef struct spColor {
    float r, g, b, a;
} spColor;

typedef struct spTriangulator {
    struct spArrayFloatArray* convexPolygons;
    struct spArrayShortArray* convexPolygonsIndices;
    struct spShortArray* indicesArray;
    struct spIntArray* isConcaveArray;
    struct spShortArray* triangles;
    struct spArrayFloatArray* polygonPool;
    struct spArrayShortArray* polygonIndicesPool;
} spTriangulator;

typedef struct spRegionAttachment {
    struct spAttachment super;
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

typedef struct spAttachment {
    const char* name;
    int type; /* spAttachmentType enum */
    const void* vtable;
    int refCount;
    struct spAttachmentLoader* attachmentLoader;
} spAttachment;

typedef struct spTransformConstraint {
    struct spTransformConstraintData* data;
    int bonesCount;
    struct spBone** bones;
    struct spBone* target;
    float rotateMix, translateMix, scaleMix, shearMix;
    int active; /* boolean */
} spTransformConstraint;

typedef struct spSkeletonJson {
    float scale;
    struct spAttachmentLoader* attachmentLoader;
    const char* error;
} spSkeletonJson;

typedef struct spIkConstraintData {
    const char* name;
    int order;
    int skinRequired; /* bool */
    int bonesCount;
    struct spBoneData** bones;
    struct spBoneData* target;
    int bendDirection;
    int compress; /* bool */
    int stretch; /* bool */
    int uniform; /* bool */
    float mix;
    float softness;
} spIkConstraintData;

typedef struct spAnimationStateData {
    struct spSkeletonData* skeletonData;
    float defaultMix;
    const void* entries;
} spAnimationStateData;

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

typedef struct spSkin {
    const char* name;

    struct spBoneDataArray* bones;
    struct spIkConstraintDataArray* ikConstraints;
    struct spTransformConstraintDataArray* transformConstraints;
    struct spPathConstraintDataArray* pathConstraints;
} spSkin;

typedef struct spVertexEffect {
    void (*begin)(void*);
    void (*transform)(void*, float*, int);
    void (*end)(void*);
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

typedef struct spSkeletonBinary {
    float scale;
    spAttachmentLoader* attachmentLoader;
    const char* error;
} spSkeletonBinary;

typedef struct spSkeletonData {
    const char* version;
    const char* hash;
    float x, y, width, height;

    int stringsCount;
    char** strings;

    int bonesCount;
    struct spBoneData** bones;

    int slotsCount;
    spSlotData** slots;

    int skinsCount;
    spSkin** skins;
    spSkin* defaultSkin;

    int eventsCount;
    spEventData** events;

    int animationsCount;
    spAnimation** animations;

    int ikConstraintsCount;
    spIkConstraintData** ikConstraints;

    int transformConstraintsCount;
    spTransformConstraintData** transformConstraints;

    int pathConstraintsCount;
    spPathConstraintData** pathConstraints;
} spSkeletonData;

typedef struct spPathConstraintData {
    const char* name;
    int order;
    int skinRequired;
    int bonesCount;
    struct spBoneData** bones;
    struct spSlotData* target;
    int positionMode;
    int spacingMode;
    int rotateMode;
    float rotation;
    float position;
    float spacing;
    float mixRotate;
    float mixX;
    float mixY;
} spPathConstraintData;

typedef struct spBoneData {
    const char* name;
    struct spBoneData* parent;
    float length;
    float x, y;
    float rotation;
    float scaleX, scaleY;
    float shearX, shearY;
    int transformMode;
    int skinRequired;
    float color[4];
} spBoneData;

typedef struct spBone {
    spBoneData* data;
    spSkeleton* skeleton;
    spBone* parent;
    spBone** children;
    int childrenCount;

    float x, y;
    float rotation;
    float scaleX, scaleY;
    float shearX, shearY;

    float ax, ay;
    float arotation;
    float ascaleX, ascaleY;
    float ashearX, ashearY;

    float appliedValid;

    float worldX, worldY;
    float worldSignX, worldSignY;
    float a, b, worldA, worldB;
    float c, d, worldC, worldD;
} spBone;

typedef struct spSlot {
    spSlotData* data;
    spBone* bone;
    struct spAttachment* attachment;
    float r, g, b, a;
    float r2, g2, b2, a2;
    float attachmentTime;
    int attachmentState;
    int darkColor; /* boolean */
} spSlot;

typedef struct spPathConstraint {
    spPathConstraintData* data;
    spSkeleton* skeleton;
    int bonesCount;
    spBone** bones;
    spSlot* target;

    int positionMode;
    int spacingMode;
    int rotateMode;

    float position;
    float spacing;
    float rotateMix;
    float translateMix;

    float* spaces;
    float* positions;
    float* worldLengths;
    float* curves;
    float* segments;
} spPathConstraint;

typedef struct spTimeline {
    int propertyId;
    void (*apply)(void*, float, float, float*, float, float, int, int, void*);
} spTimeline;



// === Function Declarations from manual_binding copy.h ===

// === Atlas ===
spAtlas* spAtlas_createFromFile(const char* path, void* rendererObject);
void spAtlas_dispose(spAtlas* atlas);


void spAtlasPage_set_createTexture(CreateTextureCallback callback);
void spAtlasPage_set_disposeTexture(DisposeTextureCallback callback);

// === SkeletonJson ===
spSkeletonJson* spSkeletonJson_create(spAtlas* atlas);
void spSkeletonJson_dispose(spSkeletonJson* json);
spSkeletonData* spSkeletonJson_readSkeletonDataFile(spSkeletonJson* json, const char* path);

// === SkeletonBinary ===
spSkeletonBinary* spSkeletonBinary_create(spAtlas* atlas);
void spSkeletonBinary_dispose(spSkeletonBinary* binary);
spSkeletonData* spSkeletonBinary_readSkeletonDataFile(spSkeletonBinary* binary, const char* path);

// === Skeleton ===
spSkeleton* spSkeleton_create(spSkeletonData* data);
void spSkeleton_dispose(spSkeleton* skeleton);
void spSkeleton_update(spSkeleton* skeleton, float deltaTime);
void spSkeleton_setSkinByName(spSkeleton* skeleton, const char* skinName);
void spSkeleton_setToSetupPose(spSkeleton* skeleton);
void spSkeleton_updateWorldTransform(spSkeleton* skeleton);

spBone* spSkeleton_findBone(spSkeleton* skeleton, const char* name);
spSlot* spSkeleton_findSlot(spSkeleton* skeleton, const char* name);
spAttachment* spSkeleton_getAttachmentForSlotName(spSkeleton* skeleton, const char* slotName, const char* attachmentName);

// === Animation State ===
spAnimationStateData* spAnimationStateData_create(spSkeletonData* skeletonData);
void spAnimationStateData_dispose(spAnimationStateData* stateData);

spAnimationState* spAnimationState_create(spAnimationStateData* stateData);
void spAnimationState_dispose(spAnimationState* state);
void spAnimationState_update(spAnimationState* state, float delta);
void spAnimationState_apply(spAnimationState* state, spSkeleton* skeleton);
int spAnimationState_setAnimationByName(spAnimationState* state, int trackIndex, const char* animationName, int loop);
int spAnimationState_addAnimationByName(spAnimationState* state, int trackIndex, const char* animationName, int loop, float delay);

void spAnimationState_setListener(spAnimationState* state, spAnimationStateListener listener);
void spAnimationState_setVertexEffect(spAnimationState* state, spVertexEffect* effect);

// === Animation ===
spAnimation* spSkeletonData_findAnimation(spSkeletonData* data, const char* name);

// === Skin ===
spSkin* spSkeletonData_findSkin(spSkeletonData* data, const char* name);
void spSkeleton_setSkin(spSkeleton* skeleton, spSkin* newSkin);

// === Constraint APIs ===
spIkConstraint* spSkeleton_findIkConstraint(spSkeleton* skeleton, const char* name);
spTransformConstraint* spSkeleton_findTransformConstraint(spSkeleton* skeleton, const char* name);
spPathConstraint* spSkeleton_findPathConstraint(spSkeleton* skeleton, const char* name);

// === Attachments ===
spAttachment* spSkeleton_getAttachmentForSlotIndex(spSkeleton* skeleton, int slotIndex, const char* attachmentName);
spRegionAttachment* spRegionAttachment_create(const char* name);
spMeshAttachment* spMeshAttachment_create(const char* name);

// === Clipping & Effects ===
spClippingAttachment* spClippingAttachment_create(const char* name);
spVertexEffect* spJitterVertexEffect_create(float jitterX, float jitterY);
void spVertexEffect_dispose(spVertexEffect* effect);

// === Event ===
spEventData* spEventData_create(const char* name);
void spEventData_dispose(spEventData* eventData);

// === Misc ===
void spSkeleton_setBonesToSetupPose(spSkeleton* skeleton);
void spSkeleton_setSlotsToSetupPose(spSkeleton* skeleton);
void spSkeleton_setAttachment(spSkeleton* skeleton, const char* slotName, const char* attachmentName);

#endif /* MANUAL_BINDING_H */
