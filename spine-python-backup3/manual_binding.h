#ifndef MANUAL_BINDING_H
#define MANUAL_BINDING_H

// === 基本结构体声明 ===

typedef struct spAtlas spAtlas;
typedef struct spAtlasPage spAtlasPage;
typedef struct spAtlasRegion spAtlasRegion;

typedef struct spSkeletonJson spSkeletonJson;
typedef struct spSkeletonBinary spSkeletonBinary;
typedef struct spSkeletonData spSkeletonData;
typedef struct spSkeleton spSkeleton;

typedef struct spSlot spSlot;
typedef struct spSlotData spSlotData;
typedef struct spBone spBone;
typedef struct spBoneData spBoneData;

typedef struct spSkin spSkin;
typedef struct spAttachment spAttachment;
typedef struct spAttachmentLoader spAttachmentLoader;
typedef struct spRegionAttachment spRegionAttachment;
typedef struct spMeshAttachment spMeshAttachment;
typedef struct spBoundingBoxAttachment spBoundingBoxAttachment;
typedef struct spClippingAttachment spClippingAttachment;
typedef struct spPointAttachment spPointAttachment;

typedef struct spAnimation spAnimation;
typedef struct spAnimationState spAnimationState;
typedef struct spAnimationStateData spAnimationStateData;

typedef struct spEvent spEvent;
typedef struct spEventData spEventData;

typedef struct spVertexEffect spVertexEffect;

typedef struct spTransformConstraint spTransformConstraint;
typedef struct spTransformConstraintData spTransformConstraintData;
typedef struct spPathConstraint spPathConstraint;
typedef struct spPathConstraintData spPathConstraintData;
typedef struct spIkConstraint spIkConstraint;
typedef struct spIkConstraintData spIkConstraintData;

// === Atlas ===

spAtlas* spAtlas_createFromFile(const char* path, void* rendererObject);
void spAtlas_dispose(spAtlas* atlas);

typedef void (*CreateTextureCallback)(spAtlasPage* page, const char* path);
typedef void (*DisposeTextureCallback)(spAtlasPage* page);

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

typedef void (*spAnimationStateListener)(spAnimationState* state, int trackIndex, int eventType, spEvent* event, int loopCount);
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
