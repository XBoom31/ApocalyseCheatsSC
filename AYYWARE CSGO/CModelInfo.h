#pragma once
#include "stdafx.h"

enum OverrideType_t
{
	OVERRIDE_NORMAL = 0,
	OVERRIDE_BUILD_SHADOWS,
	OVERRIDE_DEPTH_WRITE,
	OVERRIDE_WHATEVER
};
typedef unsigned short MaterialHandle_t;

//-----------------------------------------------------------------------------
// forward declarations
//-----------------------------------------------------------------------------
struct mstudioanimdesc_t;
struct mstudioseqdesc_t;
class IClientRenderable;
class Vector;
struct studiohdr_t;
class IMaterial;
class CStudioHdr;
struct MaterialLightingState_t;
enum
{
	ADDDECAL_TO_ALL_LODS = -1
};
#define DECLARE_HANDLE_16BIT(name)	typedef CIntHandle16< struct name##__handle * > name;
#define DECLARE_HANDLE_32BIT(name)	typedef CIntHandle32< struct name##__handle * > name;
#define DECLARE_POINTER_HANDLE(name) struct name##__ { int unused; }; typedef struct name##__ *name
#define FORWARD_DECLARE_HANDLE(name) typedef struct name##__ *name
#define DECLARE_DERIVED_POINTER_HANDLE( _name, _basehandle ) struct _name##__ : public _basehandle##__ {}; typedef struct _name##__ *_name
#define DECLARE_ALIASED_POINTER_HANDLE( _name, _alias ) typedef struct _alias##__ *name
#define FORWARD_DECLARE_HANDLE(name) typedef struct name##__ *name
FORWARD_DECLARE_HANDLE(LightCacheHandle_t);
DECLARE_POINTER_HANDLE(StudioDecalHandle_t);
#define STUDIORENDER_DECAL_INVALID  ( (StudioDecalHandle_t)0 )
#define IMPLEMENT_OPERATOR_EQUAL( _classname )			\
	public:												\
		_classname &operator=( const _classname &src )	\
		{												\
			memcpy( this, &src, sizeof(_classname) );	\
			return *this;								\
		}

struct studioloddata_t
{
	// not needed - this is really the same as studiohwdata_t.m_NumStudioMeshes
	//int					m_NumMeshes; 
	void				*m_pMeshData; // there are studiohwdata_t.m_NumStudioMeshes of these.
	float				m_SwitchPoint;
	// one of these for each lod since we can switch to simpler materials on lower lods.
	int					numMaterials;
	IMaterial			**ppMaterials; /* will have studiohdr_t.numtextures elements allocated */
									   // hack - this needs to go away.
	int					*pMaterialFlags; /* will have studiohdr_t.numtextures elements allocated */

										 // For decals on hardware morphing, we must actually do hardware skinning
										 // For this to work, we have to hope that the total # of bones used by
										 // hw flexed verts is < than the max possible for the dx level we're running under
	int					*m_pHWMorphDecalBoneRemap;
	int					m_nDecalBoneCount;
};
struct studiohwdata_t
{
	int					m_RootLOD;	// calced and clamped, nonzero for lod culling
	int					m_NumLODs;
	studioloddata_t		*m_pLODs;
	int					m_NumStudioMeshes;

	inline float LODMetric(float unitSphereSize) const { return (unitSphereSize != 0.0f) ? (100.0f / unitSphereSize) : 0.0f; }
	inline int GetLODForMetric(float lodMetric) const
	{
		if (!m_NumLODs)
			return 0;

		// shadow lod is specified on the last lod with a negative switch
		// never consider shadow lod as viable candidate
		int numLODs = (m_pLODs[m_NumLODs - 1].m_SwitchPoint < 0.0f) ? m_NumLODs - 1 : m_NumLODs;

		for (int i = m_RootLOD; i < numLODs - 1; i++)
		{
			if (m_pLODs[i + 1].m_SwitchPoint > lodMetric)
				return i;
		}

		return numLODs - 1;
	}
};

//-----------------------------------------------------------------------------
// Model rendering state
//-----------------------------------------------------------------------------
struct DrawModelState_t
{
	studiohdr_t*			m_pStudioHdr;
	studiohwdata_t*			m_pStudioHWData;
	IClientRenderable*		m_pRenderable;
	const matrix3x4		*m_pModelToWorld;
	StudioDecalHandle_t		m_decals;
	int						m_drawFlags;
	int						m_lod;
};


//-----------------------------------------------------------------------------
// Model Rendering + instance data
//-----------------------------------------------------------------------------

// change this when the new version is incompatable with the old
#define VENGINE_HUDMODEL_INTERFACE_VERSION	"VEngineModel016"

typedef unsigned short ModelInstanceHandle_t;

enum
{
	MODEL_INSTANCE_INVALID = (ModelInstanceHandle_t)~0
};

class IMatRenderContext;
class ITexture;


struct ModelRenderInfo_t
{
	Vector origin;
	Vector angles;
	IClientRenderable *pRenderable;
	const model_t *pModel;
	const matrix3x4 *pModelToWorld;
	const matrix3x4 *pLightingOffset;
	const Vector *pLightingOrigin;
	int flags;
	int entity_index;
	int skin;
	int body;
	int hitboxset;
	ModelInstanceHandle_t instance;

};

struct StaticPropRenderInfo_t
{
	matrix3x4		*pModelToWorld;
	model_t			*pModel;
	IClientRenderable		*pRenderable;
	Vector					*pLightingOrigin;
	ModelInstanceHandle_t	instance;
	uint8					skin;
	uint8					alpha;
};

struct LightingQuery_t
{
	Vector m_LightingOrigin;
	ModelInstanceHandle_t m_InstanceHandle;
	bool m_bAmbientBoost;
};

struct StaticLightingQuery_t : public LightingQuery_t
{
	IClientRenderable *m_pRenderable;
};

struct ColorMeshInfo_t
{
	// A given color mesh can own a unique Mesh, or it can use a shared Mesh
	// (in which case it uses a sub-range defined by m_nVertOffset and m_nNumVerts)
	void				*	m_pMesh;
	void				*	m_pPooledVBAllocator;
	int						m_nVertOffsetInBytes;
	int						m_nNumVerts;
};

struct DrawModelInfo_t
{
	studiohdr_t		*m_pStudioHdr;
	studiohwdata_t	*m_pHardwareData;
	StudioDecalHandle_t m_Decals;
	int				m_Skin;
	int				m_Body;
	int				m_HitboxSet;
	void			*m_pClientEntity;
	int				m_Lod;
	void*			m_pColorMeshes;
	bool			m_bStaticLighting;
	void*			m_LightingState;

	IMPLEMENT_OPERATOR_EQUAL(DrawModelInfo_t);
};

// UNDONE: Move this to hud export code, subsume previous functions
class IVModelRender 
{
public:
	virtual int DrawModel(int flags, IClientRenderable* pRenderable, ModelInstanceHandle_t instance, int entity_index, const model_t* model, Vector const& origin, Vector const& angles, int skin, int body, int hitboxset, const matrix3x4* modelToWorld = NULL, const matrix3x4* pLightingOffset = NULL) = 0;
	virtual void ForcedMaterialOverride(IMaterial* newMaterial, OverrideType_t nOverrideType = OverrideType_t::OVERRIDE_NORMAL, int a = NULL) = 0;
	virtual bool IsForcedMaterialOverride() = 0;
	virtual void SetViewTarget(const CStudioHdr* pStudioHdr, int nBodyIndex, const Vector& target) = 0;
	virtual ModelInstanceHandle_t CreateInstance(IClientRenderable* pRenderable, LightCacheHandle_t* pCache = NULL) = 0;
	virtual void DestroyInstance(ModelInstanceHandle_t handle) = 0;
	virtual void SetStaticLighting(ModelInstanceHandle_t handle, LightCacheHandle_t* pHandle) = 0;
	virtual LightCacheHandle_t GetStaticLighting(ModelInstanceHandle_t handle) = 0;
	virtual bool ChangeInstance(ModelInstanceHandle_t handle, IClientRenderable* pRenderable) = 0;
	virtual void AddDecal(ModelInstanceHandle_t handle, Ray_t const& ray, Vector const& decalUp, int decalIndex, int body, bool noPokeThru = false, int maxLODToDecal = ADDDECAL_TO_ALL_LODS) = 0;
	virtual void RemoveAllDecals(ModelInstanceHandle_t handle) = 0;
	virtual bool ModelHasDecals(ModelInstanceHandle_t handle) = 0;
	virtual void RemoveAllDecalsFromAllModels() = 0;
	virtual matrix3x4* DrawModelShadowSetup(IClientRenderable* pRenderable, int body, int skin, DrawModelInfo_t* pInfo, matrix3x4* pCustomBoneToWorld = NULL) = 0;
	virtual void DrawModelShadow(IClientRenderable* pRenderable, const DrawModelInfo_t& info, matrix3x4* pCustomBoneToWorld = NULL) = 0;
	virtual bool RecomputeStaticLighting(ModelInstanceHandle_t handle) = 0;
	virtual void ReleaseAllStaticPropColorData() = 0;
	virtual void RestoreAllStaticPropColorData() = 0;
	virtual int DrawModelEx(ModelRenderInfo_t& pInfo) = 0;
	virtual int DrawModelExStaticProp(ModelRenderInfo_t& pInfo) = 0;
	virtual bool DrawModelSetup(ModelRenderInfo_t& pInfo, DrawModelState_t* pState, matrix3x4** ppBoneToWorldOut) = 0;
	virtual void DrawModelExecute(IMatRenderContext* ctx, const DrawModelState_t& state, const ModelRenderInfo_t& pInfo, matrix3x4* pCustomBoneToWorld = NULL) = 0;
	virtual void SetupLighting(const Vector& vecCenter) = 0;
	virtual int DrawStaticPropArrayFast(StaticPropRenderInfo_t* pProps, int count, bool bShadowDepth) = 0;
	virtual void SuppressEngineLighting(bool bSuppress) = 0;
	virtual void SetupColorMeshes(int nTotalVerts) = 0;
	virtual void SetupLightingEx(const Vector& vecCenter, ModelInstanceHandle_t handle) = 0;
	virtual bool GetBrightestShadowingLightSource(const Vector& vecCenter, Vector& lightPos, Vector& lightBrightness, bool bAllowNonTaggedLights) = 0;
	virtual void ComputeLightingState(int nCount, const LightingQuery_t* pQuery, MaterialLightingState_t* pState, ITexture** ppEnvCubemapTexture) = 0;
	virtual void GetModelDecalHandles(LPVOID* pDecals, int nDecalStride, int nCount, const ModelInstanceHandle_t* pHandles) = 0;
	virtual void ComputeStaticLightingState(int nCount, const StaticLightingQuery_t* pQuery, MaterialLightingState_t* pState, MaterialLightingState_t* pDecalState, ColorMeshInfo_t** ppStaticLighting, ITexture** ppEnvCubemapTexture, void* pColorMeshHandles) = 0;
	virtual void CleanupStaticLightingState(int nCount, void* pColorMeshHandles) = 0;

};



#define IsLinux()	IsPlatformLinux() 
#define IsOSX()		IsPlatformOSX()
#define IsPosix()	IsPlatformPosix()
#define IsX360()	IsPlatformX360()
#define IsPS3()		IsPlatformPS3()
#define DEFCONFIGMETHOD( ret_type, method, xbox_return_value )	\
virtual ret_type method const = 0;
typedef unsigned int		uint;
struct characterset_t;

class CUtlMemory
{

};

typedef void(*MaterialBufferReleaseFunc_t)(int nChangeFlags);	// see RestoreChangeFlags_t
typedef void(*MaterialBufferRestoreFunc_t)(int nChangeFlags);	// see RestoreChangeFlags_t
typedef void(*ModeChangeCallbackFunc_t)(void);
struct Rect_t
{
	int x, y;
	int width, height;
};
enum RenderTargetSizeMode_t
{
	RT_SIZE_NO_CHANGE = 0,			// Only allowed for render targets that don't want a depth buffer
									// (because if they have a depth buffer, the render target must be less than or equal to the size of the framebuffer).
	RT_SIZE_DEFAULT = 1,				// Don't play with the specified width and height other than making sure it fits in the framebuffer.
	RT_SIZE_PICMIP = 2,				// Apply picmip to the render target's width and height.
	RT_SIZE_HDR = 3,					// frame_buffer_width / 4
	RT_SIZE_FULL_FRAME_BUFFER = 4,	// Same size as frame buffer, or next lower power of 2 if we can't do that.
	RT_SIZE_OFFSCREEN = 5,			// Target of specified size, don't mess with dimensions
	RT_SIZE_FULL_FRAME_BUFFER_ROUNDED_UP = 6 // Same size as the frame buffer, rounded up if necessary for systems that can't do non-power of two textures.
};
enum MaterialRenderTargetDepth_t
{
	MATERIAL_RT_DEPTH_SHARED = 0x0,
	MATERIAL_RT_DEPTH_SEPARATE = 0x1,
	MATERIAL_RT_DEPTH_NONE = 0x2,
	MATERIAL_RT_DEPTH_ONLY = 0x3,
};
struct ApplicationInstantCountersInfo_t
{
	uint m_nCpuActivityMask;
	uint m_nDeferredWordsAllocated;
};
typedef unsigned int HTOOLHANDLE;
enum
{
	HTOOLHANDLE_INVALID = 0
};
enum CompiledVtfFlags
{
	// Flags from the *.txt config file
	TEXTUREFLAGS_POINTSAMPLE = 0x00000001,
	TEXTUREFLAGS_TRILINEAR = 0x00000002,
	TEXTUREFLAGS_CLAMPS = 0x00000004,
	TEXTUREFLAGS_CLAMPT = 0x00000008,
	TEXTUREFLAGS_ANISOTROPIC = 0x00000010,
	TEXTUREFLAGS_HINT_DXT5 = 0x00000020,
	TEXTUREFLAGS_PWL_CORRECTED = 0x00000040,
	TEXTUREFLAGS_NORMAL = 0x00000080,
	TEXTUREFLAGS_NOMIP = 0x00000100,
	TEXTUREFLAGS_NOLOD = 0x00000200,
	TEXTUREFLAGS_ALL_MIPS = 0x00000400,
	TEXTUREFLAGS_PROCEDURAL = 0x00000800,

	// These are automatically generated by vtex from the texture data.
	TEXTUREFLAGS_ONEBITALPHA = 0x00001000,
	TEXTUREFLAGS_EIGHTBITALPHA = 0x00002000,

	// Newer flags from the *.txt config file
	TEXTUREFLAGS_ENVMAP = 0x00004000,
	TEXTUREFLAGS_RENDERTARGET = 0x00008000,
	TEXTUREFLAGS_DEPTHRENDERTARGET = 0x00010000,
	TEXTUREFLAGS_NODEBUGOVERRIDE = 0x00020000,
	TEXTUREFLAGS_SINGLECOPY = 0x00040000,

	TEXTUREFLAGS_PRE_SRGB = 0x00080000, //SRGB correction has already been applied to this texture.

	TEXTUREFLAGS_UNUSED_00100000 = 0x00100000,
	TEXTUREFLAGS_UNUSED_00200000 = 0x00200000,
	TEXTUREFLAGS_UNUSED_00400000 = 0x00400000,

	TEXTUREFLAGS_NODEPTHBUFFER = 0x00800000,

	TEXTUREFLAGS_UNUSED_01000000 = 0x01000000,

	TEXTUREFLAGS_CLAMPU = 0x02000000,
	TEXTUREFLAGS_VERTEXTEXTURE = 0x04000000,	// Usable as a vertex texture
	TEXTUREFLAGS_SSBUMP = 0x08000000,

	TEXTUREFLAGS_UNUSED_10000000 = 0x10000000,

	TEXTUREFLAGS_BORDER = 0x20000000,	// Clamp to border color on all texture coordinates

	TEXTUREFLAGS_UNUSED_40000000 = 0x40000000,
	TEXTUREFLAGS_UNUSED_80000000 = 0x80000000,
};
typedef void(*EndFrameCleanupFunc_t)(void);
class IPaintMapDataManager
{
};
class IPaintMapTextureManager {

};
typedef bool(*EndFramePriorToNextContextFunc_t)(void);
struct MaterialTextureInfo_t
{
	// Exclude information:
	//		-1	texture is not subject to exclude-handling
	//		 0	texture is completely excluded
	//		>0	texture is clamped according to exclude-instruction
	int iExcludeInformation;
};
class IClientMaterialSystem
{
public:
	virtual HTOOLHANDLE GetCurrentRecordingEntity() = 0;
	virtual void PostToolMessage(HTOOLHANDLE hEntity, KeyValues *pMsg) = 0;
};
typedef void(*OnLevelShutdownFunc_t)(void *pUserData);
enum
{
	MATERIAL_ADAPTER_NAME_LENGTH = 512
};
struct MaterialSystemHardwareIdentifier_t;
struct AspectRatioInfo_t;
struct ApplicationPerformanceCountersInfo_t
{
	float msMain;
	float msMST;
	float msGPU;
	float msFlip;
	float msTotal;
};
class IShader
{

};
struct MaterialSystem_Config_t;
struct MaterialVideoMode_t
{
	int m_Width;			// if width and height are 0 and you select 
	int m_Height;			// windowed mode, it'll use the window size
	ImageFormat m_Format;	// use ImageFormats (ignored for windowed mode)
	int m_RefreshRate;		// 0 == default (ignored for windowed mode)
};
class IFileList {

};
struct MaterialAdapterInfo_t
{
	char m_pDriverName[MATERIAL_ADAPTER_NAME_LENGTH];
	unsigned int m_VendorID;
	unsigned int m_DeviceID;
	unsigned int m_SubSysID;
	unsigned int m_Revision;
	int m_nDXSupportLevel;			// This is the *preferred* dx support level
	int m_nMinDXSupportLevel;
	int m_nMaxDXSupportLevel;
	unsigned int m_nDriverVersionHigh;
	unsigned int m_nDriverVersionLow;
};
enum HDRType_t
{
	HDR_TYPE_NONE,
	HDR_TYPE_INTEGER,
	HDR_TYPE_FLOAT,
};
enum ShadowFilterMode_t
{
	SHADOWFILTERMODE_DEFAULT,
	NVIDIA_PCF = 0,
	ATI_NO_PCF_FETCH4,
	NVIDIA_PCF_CHEAP,
	ATI_NOPCF,
	GAMECONSOLE_NINE_TAP_PCF = 0,
	GAMECONSOLE_SINGLE_TAP_PCF,
	SHADOWFILTERMODE_FIRST_CHEAP_MODE
};
enum CSMQualityMode_t
{
	CSMQUALITY_VERY_LOW,
	CSMQUALITY_LOW,
	CSMQUALITY_MEDIUM,
	CSMQUALITY_HIGH,
	CSMQUALITY_TOTAL_MODES
};
enum CSMShaderMode_t
{
	CSMSHADERMODE_LOW_OR_VERY_LOW,
	CSMSHADERMODE_MEDIUM,
	CSMSHADERMODE_HIGH,
	CSMSHADERMODE_ATIFETCH4,
	CSMSHADERMODE_TOTAL_MODES
};
class IMaterialProxyFactory
{

};
enum InitReturnVal_t
{
	INIT_FAILED = 0,
	INIT_OK,

	INIT_LAST_VAL,
};
enum AppSystemTier_t
{
	APP_SYSTEM_TIER0 = 0,
	APP_SYSTEM_TIER1,
	APP_SYSTEM_TIER2,
	APP_SYSTEM_TIER3,

	APP_SYSTEM_TIER_OTHER,
};
struct AppSystemInfo_t
{
	const char *m_pModuleName;
	const char *m_pInterfaceName;
};
class GPUMemoryStats
{

};
enum MaterialContextType_t
{
	MATERIAL_HARDWARE_CONTEXT,
	MATERIAL_QUEUED_CONTEXT,
	MATERIAL_NULL_CONTEXT
};
class IAppSystem
{
public:
	// Here's where the app systems get to learn about each other 
	virtual bool Connect(CreateInterfaceFn factory) = 0; // 0
	virtual void Disconnect() = 0; // 1

								   // Here's where systems can access other interfaces implemented by this object
								   // Returns NULL if it doesn't implement the requested interface
	virtual void *QueryInterface(const char *pInterfaceName) = 0; // 2

																  // Init, shutdown
	virtual InitReturnVal_t Init() = 0; // 3
	virtual void Shutdown() = 0; // 4

								 // Returns all dependent libraries
	virtual const AppSystemInfo_t* GetDependencies() = 0; // 5

														  // Returns the tier
	virtual AppSystemTier_t GetTier() = 0; // 6

										   // Reconnect to a particular interface
	virtual void Reconnect(CreateInterfaceFn factory, const char *pInterfaceName) = 0; // 7

																					   // New virtual function added in the 26 MAY 2015 update
	virtual void UnkFunc() = 0; // 8
};
struct MaterialSystem_SortInfo_t
{
	IMaterial	*material;
	int			lightmapPageID;
};
DECLARE_POINTER_HANDLE(MaterialLock_t);
class IMatRenderContext : public IRefCounted
{
};
enum MaterialThreadMode_t
{
	MATERIAL_SINGLE_THREADED,
	MATERIAL_QUEUED_SINGLE_THREADED,
	MATERIAL_QUEUED_THREADED
};
enum VertexCompressionType_t
{
	// This indicates an uninitialized VertexCompressionType_t value
	VERTEX_COMPRESSION_INVALID = 0xFFFFFFFF,

	// 'VERTEX_COMPRESSION_NONE' means that no elements of a vertex are compressed
	VERTEX_COMPRESSION_NONE = 0,

	// Currently (more stuff may be added as needed), 'VERTEX_COMPRESSION_ON' means:
	//  - if a vertex contains VERTEX_ELEMENT_NORMAL, this is compressed
	//    (see CVertexBuilder::CompressedNormal3f)
	//  - if a vertex contains VERTEX_ELEMENT_USERDATA4 (and a normal - together defining a tangent
	//    frame, with the binormal reconstructed in the vertex shader), this is compressed
	//    (see CVertexBuilder::CompressedUserData)
	//  - if a vertex contains VERTEX_ELEMENT_BONEWEIGHTSx, this is compressed
	//    (see CVertexBuilder::CompressedBoneWeight3fv)
	VERTEX_COMPRESSION_ON = 1
};
class IMaterialSystemHardwareConfig
{
public:
	virtual int	 GetFrameBufferColorDepth() const = 0;
	virtual int  GetSamplerCount() const = 0;
	virtual bool HasSetDeviceGammaRamp() const = 0;
	virtual bool SupportsStaticControlFlow() const = 0;
	virtual VertexCompressionType_t SupportsCompressedVertices() const = 0;
	virtual int  MaximumAnisotropicLevel() const = 0;	// 0 means no anisotropic filtering
	virtual int  MaxTextureWidth() const = 0;
	virtual int  MaxTextureHeight() const = 0;
	virtual int	 TextureMemorySize() const = 0;
	virtual bool SupportsMipmappedCubemaps() const = 0;

	virtual int	 NumVertexShaderConstants() const = 0;
	virtual int	 NumPixelShaderConstants() const = 0;
	virtual int	 MaxNumLights() const = 0;
	virtual int	 MaxTextureAspectRatio() const = 0;
	virtual int	 MaxVertexShaderBlendMatrices() const = 0;
	virtual int	 MaxUserClipPlanes() const = 0;
	virtual bool UseFastClipping() const = 0;

	// This here should be the major item looked at when checking for compat
	// from anywhere other than the material system	shaders
	DEFCONFIGMETHOD(int, GetDXSupportLevel(), 98);
	virtual const char *GetShaderDLLName() const = 0;

	virtual bool ReadPixelsFromFrontBuffer() const = 0;

	// Are dx dynamic textures preferred?
	virtual bool PreferDynamicTextures() const = 0;

	DEFCONFIGMETHOD(bool, SupportsHDR(), true);

	virtual bool NeedsAAClamp() const = 0;
	virtual bool NeedsATICentroidHack() const = 0;

	// This is the max dx support level supported by the card
	virtual int	 GetMaxDXSupportLevel() const = 0;

	// Does the card specify fog color in linear space when sRGBWrites are enabled?
	virtual bool SpecifiesFogColorInLinearSpace() const = 0;

	// Does the card support sRGB reads/writes?
	DEFCONFIGMETHOD(bool, SupportsSRGB(), true);

	virtual bool FakeSRGBWrite() const = 0;

	virtual bool CanDoSRGBReadFromRTs() const = 0;

	virtual bool SupportsGLMixedSizeTargets() const = 0;

	virtual bool IsAAEnabled() const = 0;	// Is antialiasing being used?

											// NOTE: Anything after this was added after shipping HL2.
	virtual int GetVertexSamplerCount() const = 0;
	virtual int GetMaxVertexTextureDimension() const = 0;

	virtual int  MaxTextureDepth() const = 0;

	virtual HDRType_t GetHDRType() const = 0;
	virtual HDRType_t GetHardwareHDRType() const = 0;

	virtual bool SupportsStreamOffset() const = 0;

	virtual int StencilBufferBits() const = 0;
	virtual int MaxViewports() const = 0;

	virtual void OverrideStreamOffsetSupport(bool bOverrideEnabled, bool bEnableSupport) = 0;

	virtual ShadowFilterMode_t GetShadowFilterMode(bool bForceLowQualityShadows, bool bPS30) const = 0;

	virtual int NeedsShaderSRGBConversion() const = 0;

	DEFCONFIGMETHOD(bool, UsesSRGBCorrectBlending(), true);

	virtual bool HasFastVertexTextures() const = 0;
	virtual int MaxHWMorphBatchCount() const = 0;

	virtual bool SupportsHDRMode(HDRType_t nHDRMode) const = 0;

	virtual bool GetHDREnabled(void) const = 0;
	virtual void SetHDREnabled(bool bEnable) = 0;

	virtual bool SupportsBorderColor(void) const = 0;
	virtual bool SupportsFetch4(void) const = 0;

	virtual float GetShadowDepthBias() const = 0;
	virtual float GetShadowSlopeScaleDepthBias() const = 0;

	virtual bool PreferZPrepass() const = 0;

	virtual bool SuppressPixelShaderCentroidHackFixup() const = 0;
	virtual bool PreferTexturesInHWMemory() const = 0;
	virtual bool PreferHardwareSync() const = 0;
	virtual bool ActualHasFastVertexTextures() const = 0;

	virtual bool SupportsShadowDepthTextures(void) const = 0;
	virtual ImageFormat GetShadowDepthTextureFormat(void) const = 0;
	virtual ImageFormat GetHighPrecisionShadowDepthTextureFormat(void) const = 0;
	virtual ImageFormat GetNullTextureFormat(void) const = 0;
	virtual int	GetMinDXSupportLevel() const = 0;
	virtual bool IsUnsupported() const = 0;

	// Backward compat for stdshaders
#if defined ( STDSHADER_DBG_DLL_EXPORT ) || defined( STDSHADER_DX9_DLL_EXPORT )
	inline bool SupportsPixelShaders_2_b() const { return GetDXSupportLevel() >= 92; }
#endif

	virtual float GetLightMapScaleFactor() const = 0;
	virtual bool SupportsCascadedShadowMapping() const = 0;
	virtual CSMQualityMode_t GetCSMQuality() const = 0;
	virtual bool SupportsBilinearPCFSampling() const = 0;
	virtual CSMShaderMode_t GetCSMShaderMode(CSMQualityMode_t nQualityLevel) const = 0;
};
class IMaterialSystem : public IAppSystem
{
public:

	//Placeholder for API revision
	//virtual bool Connect( CreateInterfaceFn factory ) = 0;
	//virtual void Disconnect() = 0;
	//virtual void *QueryInterface( const char *pInterfaceName ) = 0;
	//virtual InitReturnVal_t Init() = 0;
	//virtual void Shutdown() = 0;

	// Call this to initialize the material system
	// returns a method to create interfaces in the shader dll
	virtual CreateInterfaceFn	Init(char const* pShaderAPIDLL,
		IMaterialProxyFactory *pMaterialProxyFactory,
		CreateInterfaceFn fileSystemFactory,
		CreateInterfaceFn cvarFactory = NULL) = 0;
	// Call this to set an explicit shader version to use 
	// Must be called before Init().
	virtual void				SetShaderAPI(char const *pShaderAPIDLL) = 0;
	// Must be called before Init(), if you're going to call it at all...
	virtual void				SetAdapter(int nAdapter, int nFlags) = 0;
	// Call this when the mod has been set up, which may occur after init
	// At this point, the game + gamebin paths have been set up
	virtual void				ModInit() = 0;
	virtual void				ModShutdown() = 0;
	virtual void				SetThreadMode(MaterialThreadMode_t mode, int nServiceThread = -1) = 0;
	virtual MaterialThreadMode_t GetThreadMode() = 0;
	virtual bool				IsRenderThreadSafe() = 0;
	virtual void				ExecuteQueued() = 0;
	virtual void				OnDebugEvent(const char *pEvent) = 0;
	virtual IMaterialSystemHardwareConfig *GetHardwareConfig(const char *pVersion, int *returnCode) = 0;
	// Call this before rendering each frame with the current config for the material system.
	// Will do whatever is necessary to get the material system into the correct state
	// upon configuration change. .doesn't much else otherwise.
	virtual bool				UpdateConfig(bool bForceUpdate) = 0;
	// Force this to be the config; update all material system convars to match the state return true if lightmaps need to be redownloaded
	virtual bool				OverrideConfig(const MaterialSystem_Config_t &config, bool bForceUpdate) = 0;
	// Get the current config for this video card (as last set by UpdateConfig)
	virtual const MaterialSystem_Config_t &GetCurrentConfigForVideoCard() const = 0;
	// Gets *recommended* configuration information associated with the display card, 
	// given a particular dx level to run under. 
	// Use dxlevel 0 to use the recommended dx level.
	// The function returns false if an invalid dxlevel was specified
	virtual bool				GetRecommendedConfigurationInfo(int nDXLevel, KeyValues * pKeyValues) = 0;
	// Gets the number of adapters...
	virtual int					GetDisplayAdapterCount() const = 0;
	// Returns the current adapter in use
	virtual int					GetCurrentAdapter() const = 0;
	// Returns info about each adapter
	virtual void				GetDisplayAdapterInfo(int adapter, MaterialAdapterInfo_t& info) const = 0;
	// Returns the number of modes
	virtual int					GetModeCount(int adapter) const = 0;
	// Returns mode information
	virtual void				GetModeInfo(int adapter, int mode, MaterialVideoMode_t& info) const = 0;
	virtual void				AddModeChangeCallBack(ModeChangeCallbackFunc_t func) = 0;
	// Returns the mode info for the current display device
	virtual void				GetDisplayMode(MaterialVideoMode_t& mode) const = 0; //21
																					 // Sets the mode
	virtual bool				SetMode(void* hwnd, const MaterialSystem_Config_t &config) = 0;
	virtual bool				SupportsMSAAMode(int nMSAAMode) = 0;
	// FIXME: REMOVE! Get video card identitier
	virtual const MaterialSystemHardwareIdentifier_t &GetVideoCardIdentifier(void) const = 0;
	// Use this to spew information about the 3D layer 
	virtual void				SpewDriverInfo() const = 0;
	// Get the image format of the back buffer. . useful when creating render targets, etc.
	virtual void				GetBackBufferDimensions(int &width, int &height) const = 0;
	virtual ImageFormat			GetBackBufferFormat() const = 0;
	virtual const AspectRatioInfo_t &GetAspectRatioInfo() const = 0;
	virtual bool				SupportsHDRMode(HDRType_t nHDRModede) = 0;
	// Creates/ destroys a child window
	virtual bool				AddView(void* hwnd) = 0;
	virtual void				RemoveView(void* hwnd) = 0; // 31
															// Sets the view
	virtual void				SetView(void* hwnd) = 0;
	virtual void				BeginFrame(float frameTime) = 0;
	virtual void				EndFrame() = 0;
	virtual void				Flush(bool flushHardware = false) = 0;
	virtual unsigned int		GetCurrentFrameCount() = 0;
	/// FIXME: This stuff needs to be cleaned up and abstracted.
	// Stuff that gets exported to the launcher through the engine
	virtual void				SwapBuffers() = 0;
	// Flushes managed textures from the texture cacher
	virtual void				EvictManagedResources() = 0;
	virtual void				ReleaseResources(void) = 0;
	virtual void				ReacquireResources(void) = 0;
	// Installs a function to be called when we need to release vertex buffers + textures
	virtual void				AddReleaseFunc(MaterialBufferReleaseFunc_t func) = 0; // 41
	virtual void				RemoveReleaseFunc(MaterialBufferReleaseFunc_t func) = 0;
	// Installs a function to be called when we need to restore vertex buffers
	virtual void				AddRestoreFunc(MaterialBufferRestoreFunc_t func) = 0;
	virtual void				RemoveRestoreFunc(MaterialBufferRestoreFunc_t func) = 0;
	// Installs a function to be called when we need to delete objects at the end of the render frame
	virtual void				AddEndFrameCleanupFunc(EndFrameCleanupFunc_t func) = 0;
	virtual void				RemoveEndFrameCleanupFunc(EndFrameCleanupFunc_t func) = 0;
	virtual void				OnLevelShutdown() = 0;
	virtual bool				AddOnLevelShutdownFunc(OnLevelShutdownFunc_t func, void *pUserData) = 0;
	virtual bool				RemoveOnLevelShutdownFunc(OnLevelShutdownFunc_t func, void *pUserData) = 0;
	virtual void				OnLevelLoadingComplete() = 0;
	// Release temporary HW memory...
	virtual void				ResetTempHWMemory(bool bExitingLevel = false) = 0; // 51
																				   // For dealing with device lost in cases where SwapBuffers isn't called all the time (Hammer)
	virtual void				HandleDeviceLost() = 0;
	// Used to iterate over all shaders for editing purposes
	// GetShaders returns the number of shaders it actually found
	virtual int					ShaderCount() const = 0;
	virtual int					GetShaders(int nFirstShader, int nMaxCount, IShader **ppShaderList) const = 0;
	// Returns shader flag names for editors to be able to edit them
	virtual int					ShaderFlagCount() const = 0;
	virtual const char *		ShaderFlagName(int nIndex) const = 0;
	// Gets the actual shader fallback for a particular shader
	virtual void				GetShaderFallback(const char *pShaderName, char *pFallbackShader, int nFallbackLength) = 0;
	virtual IMaterialProxyFactory *GetMaterialProxyFactory() = 0;
	// Sets the material proxy factory. Calling this causes all materials to be uncached.
	virtual void				SetMaterialProxyFactory(IMaterialProxyFactory* pFactory) = 0;
	// Used to enable editor materials. Must be called before Init.
	virtual void				EnableEditorMaterials() = 0;
	virtual void                EnableGBuffers() = 0; // 61
													  // Force it to ignore Draw calls.
	virtual void				SetInStubMode(bool bInStubMode) = 0;
	// Debug support
	virtual void				DebugPrintUsedMaterials(const char *pSearchSubString, bool bVerbose) = 0;
	virtual void				DebugPrintUsedTextures(void) = 0;
	virtual void				ToggleSuppressMaterial(char const* pMaterialName) = 0;
	virtual void				ToggleDebugMaterial(char const* pMaterialName) = 0;


	//---------------------------------------------------------
	// Misc features
	//---------------------------------------------------------
	//returns whether fast clipping is being used or not - needed to be exposed for better per-object clip behavior
	virtual bool				UsingFastClipping(void) = 0;

	virtual int					StencilBufferBits(void) = 0; //number of bits per pixel in the stencil buffer


															 //---------------------------------------------------------
															 // Material and texture management
															 //---------------------------------------------------------

															 // uncache all materials. .  good for forcing reload of materials.
	virtual void				UncacheAllMaterials() = 0;

	// Remove any materials from memory that aren't in use as determined
	// by the IMaterial's reference count.
	virtual void				UncacheUnusedMaterials(bool bRecomputeStateSnapshots = false) = 0;

	// Load any materials into memory that are to be used as determined
	// by the IMaterial's reference count.
	virtual void				CacheUsedMaterials() = 0; // 71

														  // Force all textures to be reloaded from disk.
	virtual void				ReloadTextures() = 0;

	// Reloads materials
	virtual void				ReloadMaterials(const char *pSubString = NULL) = 0;

	// Create a procedural material. The keyvalues looks like a VMT file
	virtual IMaterial *			CreateMaterial(const char *pMaterialName, KeyValues *pVMTKeyValues) = 0;

	// Find a material by name.
	// The name of a material is a full path to 
	// the vmt file starting from "hl2/materials" (or equivalent) without
	// a file extension.
	// eg. "dev/dev_bumptest" refers to somethign similar to:
	// "d:/hl2/hl2/materials/dev/dev_bumptest.vmt"
	// Most of the texture groups for pTextureGroupName are listed in texture_group_names.h.
	// Note: if the material can't be found, this returns a checkerboard material. You can 
	// find out if you have that material by calling IMaterial::IsErrorMaterial().
	// (Or use the global IsErrorMaterial function, which checks if it's null too).
	// 83rd virtual
	virtual IMaterial*			FindMaterial(char const* pMaterialName, const char *pTextureGroupName, bool complain = true, const char *pComplainPrefix = NULL) = 0;

	virtual void				LoadKeyValuesFromVMTFile(KeyValues& values, const char* name, bool somebool) const = 0;
	//---------------------------------
	// This is the interface for knowing what materials are available
	// is to use the following functions to get a list of materials.  The
	// material names will have the full path to the material, and that is the 
	// only way that the directory structure of the materials will be seen through this
	// interface.
	// NOTE:  This is mostly for worldcraft to get a list of materials to put
	// in the "texture" browser.in Worldcraft
	virtual MaterialHandle_t	FirstMaterial() const = 0;

	// returns InvalidMaterial if there isn't another material.
	// WARNING: you must call GetNextMaterial until it returns NULL, 
	// otherwise there will be a memory leak.
	virtual MaterialHandle_t	NextMaterial(MaterialHandle_t h) const = 0;

	// This is the invalid material
	virtual MaterialHandle_t	InvalidMaterial() const = 0;

	// Returns a particular material
	virtual IMaterial*			GetMaterial(MaterialHandle_t h) const = 0;

	// Get the total number of materials in the system.  These aren't just the used
	// materials, but the complete collection.
	virtual int					GetNumMaterials() const = 0;

	//---------------------------------

	virtual ITexture *			FindTexture(char const* pTextureName, const char *pTextureGroupName, bool complain = true) = 0;

	// Checks to see if a particular texture is loaded
	virtual bool				IsTextureLoaded(char const* pTextureName) const = 0; // 90

																					 // Creates a procedural texture
	virtual ITexture *			CreateProceduralTexture(const char	*pTextureName,
		const char *pTextureGroupName,
		int w,
		int h,
		ImageFormat fmt,
		int nFlags) = 0;

	//
	// Render targets
	//
	virtual void				BeginRenderTargetAllocation() = 0;
	virtual void				EndRenderTargetAllocation() = 0; // Simulate an Alt-Tab in here, which causes a release/restore of all resources

																 // Creates a render target
																 // If depth == true, a depth buffer is also allocated. If not, then
																 // the screen's depth buffer is used.
																 // Creates a texture for use as a render target
	virtual ITexture *			CreateRenderTargetTexture(int w,
		int h,
		RenderTargetSizeMode_t sizeMode,	// Controls how size is generated (and regenerated on video mode change).
		ImageFormat	format,
		MaterialRenderTargetDepth_t depth = MATERIAL_RT_DEPTH_SHARED) = 0;

	virtual ITexture *			CreateNamedRenderTargetTextureEx(const char *pRTName,				// Pass in NULL here for an unnamed render target.
		int w,
		int h,
		RenderTargetSizeMode_t sizeMode,	// Controls how size is generated (and regenerated on video mode change).
		ImageFormat format,
		MaterialRenderTargetDepth_t depth = MATERIAL_RT_DEPTH_SHARED,
		unsigned int textureFlags = TEXTUREFLAGS_CLAMPS | TEXTUREFLAGS_CLAMPT,
		unsigned int renderTargetFlags = 0) = 0;

	virtual ITexture *			CreateNamedRenderTargetTexture(const char *pRTName,
		int w,
		int h,
		RenderTargetSizeMode_t sizeMode,	// Controls how size is generated (and regenerated on video mode change).
		ImageFormat format,
		MaterialRenderTargetDepth_t depth = MATERIAL_RT_DEPTH_SHARED,
		bool bClampTexCoords = true,
		bool bAutoMipMap = false) = 0;

	// Must be called between the above Begin-End calls!
	virtual ITexture *			CreateNamedRenderTargetTextureEx2(const char *pRTName,				// Pass in NULL here for an unnamed render target.
		int w,
		int h,
		RenderTargetSizeMode_t sizeMode,	// Controls how size is generated (and regenerated on video mode change).
		ImageFormat format,
		MaterialRenderTargetDepth_t depth = MATERIAL_RT_DEPTH_SHARED,
		unsigned int textureFlags = TEXTUREFLAGS_CLAMPS | TEXTUREFLAGS_CLAMPT,
		unsigned int renderTargetFlags = 0) = 0;

	// -----------------------------------------------------------
	// Lightmaps
	// -----------------------------------------------------------

	// To allocate lightmaps, sort the whole world by material twice.
	// The first time through, call AllocateLightmap for every surface.
	// that has a lightmap.
	// The second time through, call AllocateWhiteLightmap for every 
	// surface that expects to use shaders that expect lightmaps.
	virtual void				BeginLightmapAllocation() = 0;
	virtual void				EndLightmapAllocation() = 0;

	virtual void				CleanupLightmaps() = 0; // 100

														// returns the sorting id for this surface
	virtual int 				AllocateLightmap(int width, int height,
		int offsetIntoLightmapPage[2],
		IMaterial *pMaterial) = 0;
	// returns the sorting id for this surface
	virtual int					AllocateWhiteLightmap(IMaterial *pMaterial) = 0;

	// lightmaps are in linear color space
	// lightmapPageID is returned by GetLightmapPageIDForSortID
	// lightmapSize and offsetIntoLightmapPage are returned by AllocateLightmap.
	// You should never call UpdateLightmap for a lightmap allocated through
	// AllocateWhiteLightmap.
	virtual void				UpdateLightmap(int lightmapPageID, int lightmapSize[2],
		int offsetIntoLightmapPage[2],
		float *pFloatImage, float *pFloatImageBump1,
		float *pFloatImageBump2, float *pFloatImageBump3) = 0;
	virtual int					GetNumSortIDs() = 0;
	virtual void				GetSortInfo(MaterialSystem_SortInfo_t *sortInfoArray) = 0;
	// Read the page size of an existing lightmap by sort id (returned from AllocateLightmap())
	virtual void				GetLightmapPageSize(int lightmap, int *width, int *height) const = 0;
	virtual void				ResetMaterialLightmapPageInfo() = 0;
	virtual bool				IsStereoSupported() = 0;
	virtual bool				IsStereoActiveThisFrame() const = 0;
	virtual void				NVStereoUpdate() = 0;
	virtual void				ClearBuffers(bool bClearColor, bool bClearDepth, bool bClearStencil = false) = 0;
	virtual void				SpinPresent(unsigned int nFrames) = 0;

	// -----------------------------------------------------------
	// Access the render contexts
	// -----------------------------------------------------------

	//IMatRenderContext* GetContext()
	//{
	//	typedef IMatRenderContext*(__thiscall* OriginalFn)(PVOID);
	//	return getvfunc<OriginalFn>(this, 114)(this);
	//}

	virtual IMatRenderContext*	GetRenderContext() = 0; // 114
	virtual void				BeginUpdateLightmaps(void) = 0;
	virtual void				EndUpdateLightmaps(void) = 0;
	// -----------------------------------------------------------
	// Methods to force the material system into non-threaded, non-queued mode
	// -----------------------------------------------------------
	virtual MaterialLock_t		Lock() = 0;
	virtual void				Unlock(MaterialLock_t) = 0;
	// Create a custom render context. Cannot be used to create MATERIAL_HARDWARE_CONTEXT
	virtual IMatRenderContext *CreateRenderContext(MaterialContextType_t type) = 0;
	// Set a specified render context to be the global context for the thread. Returns the prior context.
	virtual IMatRenderContext *SetRenderContext(IMatRenderContext *) = 0;
	virtual bool				SupportsCSAAMode(int nNumSamples, int nQualityLevel) = 0;
	virtual void				RemoveModeChangeCallBack(ModeChangeCallbackFunc_t func) = 0;
	// Finds or create a procedural material.
	virtual IMaterial *			FindProceduralMaterial(const char *pMaterialName, const char *pTextureGroupName, KeyValues *pVMTKeyValues) = 0;
	virtual void				AddTextureAlias(const char *pAlias, const char *pRealName) = 0;
	virtual void				RemoveTextureAlias(const char *pAlias) = 0;
	// returns a lightmap page ID for this allocation, -1 if none available
	// frameID is a number that should be changed every frame to prevent locking any textures that are
	// being used to draw in the previous frame
	virtual int					AllocateDynamicLightmap(int lightmapSize[2], int *pOutOffsetIntoPage, int frameID) = 0;
	virtual void				SetExcludedTextures(const char *pScriptName, bool bUsingWeaponModelCache) = 0;
	virtual void				UpdateExcludedTextures(void) = 0;
	virtual bool				IsInFrame() const = 0;
	virtual void				CompactMemory() = 0;
	virtual void				GetGPUMemoryStats(GPUMemoryStats &stats) = 0;
	// For sv_pure mode. The filesystem figures out which files the client needs to reload to be "pure" ala the server's preferences.
	virtual void				ReloadFilesInList(IFileList *pFilesToReload) = 0;
	// Get information about the texture for texture management tools
	virtual bool				GetTextureInformation(char const *szTextureName, MaterialTextureInfo_t &info) const = 0;
	// call this once the render targets are allocated permanently at the beginning of the game
	virtual void				FinishRenderTargetAllocation(void) = 0;
	virtual void				ReEnableRenderTargetAllocation_IRealizeIfICallThisAllTexturesWillBeUnloadedAndLoadTimeWillSufferHorribly(void) = 0;
	virtual	bool				AllowThreading(bool bAllow, int nServiceThread) = 0;
	virtual bool				GetRecommendedVideoConfig(KeyValues *pKeyValues) = 0;
	virtual IClientMaterialSystem*	GetClientMaterialSystemInterface() = 0;
	virtual bool				CanDownloadTextures() const = 0;
	virtual int					GetNumLightmapPages() const = 0;
	virtual IPaintMapTextureManager *RegisterPaintMapDataManager(IPaintMapDataManager *pDataManager) = 0; //You supply an interface we can query for bits, it gives back an interface you can use to drive updates
	virtual void				BeginUpdatePaintmaps() = 0;
	virtual void				EndUpdatePaintmaps() = 0;
	virtual void				UpdatePaintmap(int paintmap, unsigned char *pPaintData, int numRects, Rect_t *pRects) = 0;
	virtual ITexture			*CreateNamedMultiRenderTargetTexture(const char *pRTName, int w, int h, RenderTargetSizeMode_t sizeMode,
		ImageFormat format, MaterialRenderTargetDepth_t depth, unsigned int textureFlags, unsigned int renderTargetFlags) = 0;
	virtual void				RefreshFrontBufferNonInteractive() = 0;
	virtual uint32				GetFrameTimestamps(ApplicationPerformanceCountersInfo_t &apci, ApplicationInstantCountersInfo_t &aici) = 0;
	virtual void				DoStartupShaderPreloading() = 0;
	virtual void				AddEndFramePriorToNextContextFunc(EndFramePriorToNextContextFunc_t func) = 0;
	virtual void				RemoveEndFramePriorToNextContextFunc(EndFramePriorToNextContextFunc_t func) = 0;
};
class CByteswap
{
};
class CUtlBuffer
{
	// Brian has on his todo list to revisit this as there are issues in some cases with CUtlVector using operator = instead of copy construtor in InsertMultiple, etc.
	// The unsafe case is something like this:
	//  CUtlVector< CUtlBuffer > vecFoo;
	// 
	//  CUtlBuffer buf;
	//  buf.Put( xxx );
	//  vecFoo.Insert( buf );
	//
	//  This will cause memory corruption when vecFoo is cleared
	//
	//private:
	//	// Disallow copying
	//	CUtlBuffer( const CUtlBuffer & );// { Assert( 0 ); }
	//	CUtlBuffer &operator=( const CUtlBuffer & );//  { Assert( 0 ); return *this; }

public:
	enum SeekType_t
	{
		SEEK_HEAD = 0,
		SEEK_CURRENT,
		SEEK_TAIL
	};

	// flags
	enum BufferFlags_t
	{
		TEXT_BUFFER = 0x1,			// Describes how get + put work (as strings, or binary)
		EXTERNAL_GROWABLE = 0x2,	// This is used w/ external buffers and causes the utlbuf to switch to reallocatable memory if an overflow happens when Putting.
		CONTAINS_CRLF = 0x4,		// For text buffers only, does this contain \n or \n\r?
		READ_ONLY = 0x8,			// For external buffers; prevents null termination from happening.
		AUTO_TABS_DISABLED = 0x10,	// Used to disable/enable push/pop tabs
	};

	// Overflow functions when a get or put overflows
	typedef bool (CUtlBuffer::*UtlBufferOverflowFunc_t)(int nSize);

	// Constructors for growable + external buffers for serialization/unserialization
	CUtlBuffer(int growSize = 0, int initSize = 0, int nFlags = 0);
	CUtlBuffer(const void* pBuffer, int size, int nFlags = 0);
	// This one isn't actually defined so that we catch contructors that are trying to pass a bool in as the third param.
	CUtlBuffer(const void *pBuffer, int size, bool crap);

	unsigned char	GetFlags() const;

	// NOTE: This will assert if you attempt to recast it in a way that
	// is not compatible. The only valid conversion is binary-> text w/CRLF
	void			SetBufferType(bool bIsText, bool bContainsCRLF);

	// Makes sure we've got at least this much memory
	void			EnsureCapacity(int num);

	// Access for direct read into buffer
	void *			AccessForDirectRead(int nBytes);

	// Attaches the buffer to external memory....
	void			SetExternalBuffer(void* pMemory, int nSize, int nInitialPut, int nFlags = 0);
	bool			IsExternallyAllocated() const;
	void			AssumeMemory(void *pMemory, int nSize, int nInitialPut, int nFlags = 0);
	void			*Detach();
	void*			DetachMemory();

	FORCEINLINE void ActivateByteSwappingIfBigEndian(void)
	{

	}


	// Controls endian-ness of binary utlbufs - default matches the current platform
	void			ActivateByteSwapping(bool bActivate);
	void			SetBigEndian(bool bigEndian);
	bool			IsBigEndian(void);

	// Resets the buffer; but doesn't free memory
	void			Clear();

	// Clears out the buffer; frees memory
	void			Purge();

	// Dump the buffer to stdout
	void			Spew();

	// Read stuff out.
	// Binary mode: it'll just read the bits directly in, and characters will be
	//		read for strings until a null character is reached.
	// Text mode: it'll parse the file, turning text #s into real numbers.
	//		GetString will read a string until a space is reached
	char			GetChar();
	unsigned char	GetUnsignedChar();
	short			GetShort();
	unsigned short	GetUnsignedShort();
	int				GetInt();
	int64			GetInt64();
	unsigned int	GetIntHex();
	unsigned int	GetUnsignedInt();
	float			GetFloat();
	double			GetDouble();
	void *			GetPtr();
	void			GetString(char* pString, int nMaxChars = 0);
	void			Get(void* pMem, int size);
	void			GetLine(char* pLine, int nMaxChars = 0);

	// Used for getting objects that have a byteswap datadesc defined
	template <typename T> void GetObjects(T *dest, int count = 1);

	// This will get at least 1 byte and up to nSize bytes. 
	// It will return the number of bytes actually read.
	int				GetUpTo(void *pMem, int nSize);

	// This version of GetString converts \" to \\ and " to \, etc.
	// It also reads a " at the beginning and end of the string
	void			GetDelimitedString(void *pConv, char *pString, int nMaxChars = 0);
	char			GetDelimitedChar(void *pConv);

	// This will return the # of characters of the string about to be read out
	// NOTE: The count will *include* the terminating 0!!
	// In binary mode, it's the number of characters until the next 0
	// In text mode, it's the number of characters until the next space.
	int				PeekStringLength();

	// This version of PeekStringLength converts \" to \\ and " to \, etc.
	// It also reads a " at the beginning and end of the string
	// NOTE: The count will *include* the terminating 0!!
	// In binary mode, it's the number of characters until the next 0
	// In text mode, it's the number of characters between "s (checking for \")
	// Specifying false for bActualSize will return the pre-translated number of characters
	// including the delimiters and the escape characters. So, \n counts as 2 characters when bActualSize == false
	// and only 1 character when bActualSize == true
	int				PeekDelimitedStringLength(void *pConv, bool bActualSize = true);

	// Just like scanf, but doesn't work in binary mode
	int				Scanf(const char* pFmt, ...);
	int				VaScanf(const char* pFmt, va_list list);

	// Eats white space, advances Get index
	void			EatWhiteSpace();

	// Eats C++ style comments
	bool			EatCPPComment();

	// (For text buffers only)
	// Parse a token from the buffer:
	// Grab all text that lies between a starting delimiter + ending delimiter
	// (skipping whitespace that leads + trails both delimiters).
	// If successful, the get index is advanced and the function returns true,
	// otherwise the index is not advanced and the function returns false.
	bool			ParseToken(const char *pStartingDelim, const char *pEndingDelim, char* pString, int nMaxLen);

	// Advance the get index until after the particular string is found
	// Do not eat whitespace before starting. Return false if it failed
	// String test is case-insensitive.
	bool			GetToken(const char *pToken);

	// Parses the next token, given a set of character breaks to stop at
	// Returns the length of the token parsed in bytes (-1 if none parsed)
	int				ParseToken(characterset_t *pBreaks, char *pTokenBuf, int nMaxLen, bool bParseComments = true);

	// Write stuff in
	// Binary mode: it'll just write the bits directly in, and strings will be
	//		written with a null terminating character
	// Text mode: it'll convert the numbers to text versions
	//		PutString will not write a terminating character
	void			PutChar(char c);
	void			PutUnsignedChar(unsigned char uc);
	void			PutShort(short s);
	void			PutUnsignedShort(unsigned short us);
	void			PutInt(int i);
	void			PutInt64(int64 i);
	void			PutUnsignedInt(unsigned int u);
	void			PutFloat(float f);
	void			PutDouble(double d);
	void			PutPtr(void *); // Writes the pointer, not the pointed to
	void			PutString(const char* pString);
	void			Put(const void* pMem, int size);

	// Used for putting objects that have a byteswap datadesc defined
	template <typename T> void PutObjects(T *src, int count = 1);

	// This version of PutString converts \ to \\ and " to \", etc.
	// It also places " at the beginning and end of the string
	void			PutDelimitedString(void *pConv, const char *pString);
	void			PutDelimitedChar(void *pConv, char c);

	// Just like printf, writes a terminating zero in binary mode
	void			PrintAAAAAf(const char* pFmt, ...);
	void			VaPrintf(const char* pFmt, va_list list);

	// What am I writing (put)/reading (get)?
	void* PeekPut(int offset = 0);
	const void* PeekGet(int offset = 0) const;
	const void* PeekGet(int nMaxSize, int nOffset);

	// Where am I writing (put)/reading (get)?
	int TellPut() const;
	int TellGet() const;

	// What's the most I've ever written?
	int TellMaxPut() const;

	// How many bytes remain to be read?
	// NOTE: This is not accurate for streaming text files; it overshoots
	int GetBytesRemaining() const;

	// Change where I'm writing (put)/reading (get)
	void SeekPut(SeekType_t type, int offset);
	void SeekGet(SeekType_t type, int offset);

	// Buffer base
	const void* Base() const;
	void* Base();

	// memory allocation size, does *not* reflect size written or read,
	//	use TellPut or TellGet for that
	int Size() const;

	// Am I a text buffer?
	bool IsText() const;

	// Can I grow if I'm externally allocated?
	bool IsGrowable() const;

	// Am I valid? (overflow or underflow error), Once invalid it stays invalid
	bool IsValid() const;

	// Do I contain carriage return/linefeeds? 
	bool ContainsCRLF() const;

	// Am I read-only
	bool IsReadOnly() const;

	// Converts a buffer from a CRLF buffer to a CR buffer (and back)
	// Returns false if no conversion was necessary (and outBuf is left untouched)
	// If the conversion occurs, outBuf will be cleared.
	bool ConvertCRLF(CUtlBuffer &outBuf);

	// Push/pop pretty-printing tabs
	void PushTab();
	void PopTab();

	// Temporarily disables pretty print
	void EnableTabs(bool bEnable);

protected:
	// error flags
	enum
	{
		PUT_OVERFLOW = 0x1,
		GET_OVERFLOW = 0x2,
		MAX_ERROR_FLAG = GET_OVERFLOW,
	};

	void SetOverflowFuncs(UtlBufferOverflowFunc_t getFunc, UtlBufferOverflowFunc_t putFunc);

	bool OnPutOverflow(int nSize);
	bool OnGetOverflow(int nSize);

protected:
	// Checks if a get/put is ok
	bool CheckPut(int size);
	bool CheckGet(int size);

	void AddNullTermination();

	// Methods to help with pretty-printing
	bool WasLastCharacterCR();
	void PutTabs();

	// Help with delimited stuff
	char GetDelimitedCharInternal(void *pConv);
	void PutDelimitedCharInternal(void *pConv, char c);

	// Default overflow funcs
	bool PutOverflow(int nSize);
	bool GetOverflow(int nSize);

	// Does the next bytes of the buffer match a pattern?
	bool PeekStringMatch(int nOffset, const char *pString, int nLen);

	// Peek size of line to come, check memory bound
	int	PeekLineLength();

	// How much whitespace should I skip?
	int PeekWhiteSpace(int nOffset);

	// Checks if a peek get is ok
	bool CheckPeekGet(int nOffset, int nSize);

	// Call this to peek arbitrarily long into memory. It doesn't fail unless
	// it can't read *anything* new
	bool CheckArbitraryPeekGet(int nOffset, int &nIncrement);

	template <typename T> void GetType(T& dest);
	template <typename T> void GetTypeBin(T& dest);
	template <typename T> bool GetTypeText(T &value, int nRadix = 10);
	template <typename T> void GetObject(T *src);

	template <typename T> void PutType(T src);
	template <typename T> void PutTypeBin(T src);
	template <typename T> void PutObject(T *src);

	CUtlMemory m_Memory;
	int m_Get;
	int m_Put;

	unsigned char m_Error;
	unsigned char m_Flags;
	unsigned char m_Reserved;
#if defined( _X360 )
	unsigned char pad;
#endif

	int m_nTab;
	int m_nMaxPut;
	int m_nOffset;

	UtlBufferOverflowFunc_t m_GetOverflowFunc;
	UtlBufferOverflowFunc_t m_PutOverflowFunc;

	CByteswap	m_Byteswap;
};
enum RenderableTranslucencyType_t
{
	RENDERABLE_IS_OPAQUE = 0,
	RENDERABLE_IS_TRANSLUCENT,
	RENDERABLE_IS_TWO_PASS,	// has both translucent and opaque sub-partsa
};
typedef unsigned short MDLHandle_t;

class IVModelInfo
{
public:
	virtual							~IVModelInfo(void) { }
	virtual const model_t			*GetModel(int modelindex) const = 0;
	// Returns index of model by name
	virtual int						GetModelIndex(const char *name) const = 0;
	// Returns name of model
	virtual const char				*GetModelName(const model_t *model) const = 0;
	virtual void					*GetVCollide(const model_t *model) const = 0;
	virtual void					*GetVCollide(int modelindex) const = 0;
	virtual void					GetModelBounds(const model_t *model, Vector& mins, Vector& maxs) const = 0;
	virtual	void					GetModelRenderBounds(const model_t *model, Vector& mins, Vector& maxs) const = 0;
	virtual int						GetModelFrameCount(const model_t *model) const = 0;
	virtual int						GetModelType(const model_t *model) const = 0;
	virtual void					*GetModelExtraData(const model_t *model) = 0;
	virtual bool					ModelHasMaterialProxy(const model_t *model) const = 0;
	virtual bool					IsTranslucent(model_t const* model) const = 0;
	virtual bool					IsTranslucentTwoPass(const model_t *model) const = 0;
	virtual void					Unused0() {};
	virtual RenderableTranslucencyType_t ComputeTranslucencyType(const model_t *model, int nSkin, int nBody) = 0;
	virtual int						GetModelMaterialCount(const model_t* model) const = 0;
	virtual void					GetModelMaterials(const model_t *model, int count, IMaterial** ppMaterials) = 0;
	virtual bool					IsModelVertexLit(const model_t *model) const = 0;
	virtual const char				*GetModelKeyValueText(const model_t *model) = 0;
	virtual bool					GetModelKeyValue(const model_t *model, CUtlBuffer &buf) = 0; // supports keyvalue blocks in submodels
	virtual float					GetModelRadius(const model_t *model) = 0;

	virtual const studiohdr_t		*FindModel(const studiohdr_t *pStudioHdr, void **cache, const char *modelname) const = 0;
	virtual const studiohdr_t		*FindModel(void *cache) const = 0;
	virtual	void					*GetVirtualModel(const studiohdr_t *pStudioHdr) const = 0;
	virtual byte					*GetAnimBlock(const studiohdr_t *pStudioHdr, int iBlock) const = 0;
	virtual bool					HasAnimBlockBeenPreloaded(studiohdr_t const*, int) const = 0;

	// Available on client only!!!
	virtual void					GetModelMaterialColorAndLighting(const model_t *model, Vector const& origin,
		Vector const& angles, trace_t* pTrace,
		Vector& lighting, Vector& matColor) = 0;
	virtual void					GetIlluminationPoint(const model_t *model, IClientRenderable *pRenderable, Vector const& origin,
		Vector const& angles, Vector* pLightingCenter) = 0;

	virtual int						GetModelContents(int modelIndex) const = 0;
	virtual studiohdr_t				*GetStudioModel(const model_t *mod) = 0;
	virtual int						GetModelSpriteWidth(const model_t *model) const = 0;
	virtual int						GetModelSpriteHeight(const model_t *model) const = 0;

	// Sets/gets a map-specified fade range (client only)
	virtual void					SetLevelScreenFadeRange(float flMinSize, float flMaxSize) = 0;
	virtual void					GetLevelScreenFadeRange(float *pMinArea, float *pMaxArea) const = 0;

	// Sets/gets a map-specified per-view fade range (client only)
	virtual void					SetViewScreenFadeRange(float flMinSize, float flMaxSize) = 0;

	// Computes fade alpha based on distance fade + screen fade (client only)
	virtual unsigned char			ComputeLevelScreenFade(const Vector &vecAbsOrigin, float flRadius, float flFadeScale) const = 0;
	virtual unsigned char			ComputeViewScreenFade(const Vector &vecAbsOrigin, float flRadius, float flFadeScale) const = 0;

	// both client and server
	virtual int						GetAutoplayList(const studiohdr_t *pStudioHdr, unsigned short **pAutoplayList) const = 0;

	// Gets a virtual terrain collision model (creates if necessary)
	// NOTE: This may return NULL if the terrain model cannot be virtualized
	virtual void*					*GetCollideForVirtualTerrain(int index) = 0;
	virtual bool					IsUsingFBTexture(const model_t *model, int nSkin, int nBody, void /*IClientRenderable*/ *pClientRenderable) const = 0;
	virtual const model_t			*FindOrLoadModel(const char *name) const = 0;
	virtual MDLHandle_t				GetCacheHandle(const model_t *model) const = 0;
	// Returns planes of non-nodraw brush model surfaces
	virtual int						GetBrushModelPlaneCount(const model_t *model) const = 0;
	virtual void					GetBrushModelPlane(const model_t *model, int nIndex, cplane_t &plane, Vector *pOrigin) const = 0;
	virtual int						GetSurfacepropsForVirtualTerrain(int index) = 0;
	virtual bool					UsesEnvCubemap(const model_t *model) const = 0;
	virtual bool					UsesStaticLighting(const model_t *model) const = 0;
};


class IVModelInfoClient : public IVModelInfo
{
public:
};


struct virtualterrainparams_t
{
	// UNDONE: Add grouping here, specified in BSP file? (test grouping to see if this is necessary)
	int index;
};