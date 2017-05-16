#pragma once
#include "stdafx.h"
enum PreviewImageRetVal_t
{
	MATERIAL_PREVIEW_IMAGE_BAD = 0,
	MATERIAL_PREVIEW_IMAGE_OK,
	MATERIAL_NO_PREVIEW_IMAGE,
};
enum ImageFormat
{
	IMAGE_FORMAT_UNKNOWN = -1,
	IMAGE_FORMAT_RGBA8888 = 0,
	IMAGE_FORMAT_ABGR8888,
	IMAGE_FORMAT_RGB888,
	IMAGE_FORMAT_BGR888,
	IMAGE_FORMAT_RGB565,
	IMAGE_FORMAT_I8,
	IMAGE_FORMAT_IA88,
	IMAGE_FORMAT_P8,
	IMAGE_FORMAT_A8,
	IMAGE_FORMAT_RGB888_BLUESCREEN,
	IMAGE_FORMAT_BGR888_BLUESCREEN,
	IMAGE_FORMAT_ARGB8888,
	IMAGE_FORMAT_BGRA8888,
	IMAGE_FORMAT_DXT1,
	IMAGE_FORMAT_DXT3,
	IMAGE_FORMAT_DXT5,
	IMAGE_FORMAT_BGRX8888,
	IMAGE_FORMAT_BGR565,
	IMAGE_FORMAT_BGRX5551,
	IMAGE_FORMAT_BGRA4444,
	IMAGE_FORMAT_DXT1_ONEBITALPHA,
	IMAGE_FORMAT_BGRA5551,
	IMAGE_FORMAT_UV88,
	IMAGE_FORMAT_UVWQ8888,
	IMAGE_FORMAT_RGBA16161616F,
	IMAGE_FORMAT_RGBA16161616,
	IMAGE_FORMAT_UVLX8888,
	IMAGE_FORMAT_R32F,			// Single-channel 32-bit floating point
	IMAGE_FORMAT_RGB323232F,	// NOTE: D3D9 does not have this format
	IMAGE_FORMAT_RGBA32323232F,
	IMAGE_FORMAT_RG1616F,
	IMAGE_FORMAT_RG3232F,
	IMAGE_FORMAT_RGBX8888,

	IMAGE_FORMAT_NULL,			// Dummy format which takes no video memory

								// Compressed normal map formats
	IMAGE_FORMAT_ATI2N,			// One-surface ATI2N / DXN format
	IMAGE_FORMAT_ATI1N,			// Two-surface ATI1N format

	IMAGE_FORMAT_RGBA1010102,	// 10 bit-per component render targets
	IMAGE_FORMAT_BGRA1010102,
	IMAGE_FORMAT_R16F,			// 16 bit FP format

								// Depth-stencil texture formats
	IMAGE_FORMAT_D16,
	IMAGE_FORMAT_D15S1,
	IMAGE_FORMAT_D32,
	IMAGE_FORMAT_D24S8,
	IMAGE_FORMAT_LINEAR_D24S8,
	IMAGE_FORMAT_D24X8,
	IMAGE_FORMAT_D24X4S4,
	IMAGE_FORMAT_D24FS8,
	IMAGE_FORMAT_D16_SHADOW,	// Specific formats for shadow mapping
	IMAGE_FORMAT_D24X8_SHADOW,	// Specific formats for shadow mapping

								// supporting these specific formats as non-tiled for procedural cpu access (360-specific)
	IMAGE_FORMAT_LINEAR_BGRX8888,
	IMAGE_FORMAT_LINEAR_RGBA8888,
	IMAGE_FORMAT_LINEAR_ABGR8888,
	IMAGE_FORMAT_LINEAR_ARGB8888,
	IMAGE_FORMAT_LINEAR_BGRA8888,
	IMAGE_FORMAT_LINEAR_RGB888,
	IMAGE_FORMAT_LINEAR_BGR888,
	IMAGE_FORMAT_LINEAR_BGRX5551,
	IMAGE_FORMAT_LINEAR_I8,
	IMAGE_FORMAT_LINEAR_RGBA16161616,

	IMAGE_FORMAT_LE_BGRX8888,
	IMAGE_FORMAT_LE_BGRA8888,

	NUM_IMAGE_FORMATS
};
enum MaterialVarType_t
{
	MATERIAL_VAR_TYPE_FLOAT = 0,
	MATERIAL_VAR_TYPE_STRING,
	MATERIAL_VAR_TYPE_VECTOR,
	MATERIAL_VAR_TYPE_TEXTURE,
	MATERIAL_VAR_TYPE_INT,
	MATERIAL_VAR_TYPE_FOURCC,
	MATERIAL_VAR_TYPE_UNDEFINED,
	MATERIAL_VAR_TYPE_MATRIX,
	MATERIAL_VAR_TYPE_MATERIAL,
};
class CUtlSymbol
{
public:

protected:

};
typedef unsigned short MaterialVarSym_t;
class ITexture
{
public:
	// Various texture polling methods
	virtual const char *GetName(void) const = 0;
	virtual int GetMappingWidth() const = 0;
	virtual int GetMappingHeight() const = 0;
	virtual int GetActualWidth() const = 0;
	virtual int GetActualHeight() const = 0;
	virtual int GetNumAnimationFrames() const = 0;
	virtual bool IsTranslucent() const = 0;
	virtual bool IsMipmapped() const = 0;

	virtual void GetLowResColorSample(float s, float t, float *color) const = 0;

	// Gets texture resource data of the specified type.
	// Params:
	//		eDataType		type of resource to retrieve.
	//		pnumBytes		on return is the number of bytes available in the read-only data buffer or is undefined
	// Returns:
	//		pointer to the resource data, or NULL
	virtual void *GetResourceData(uint32 eDataType, size_t *pNumBytes) const = 0;

	// Methods associated with reference count
	virtual void IncrementReferenceCount(void) = 0;
	virtual void DecrementReferenceCount(void) = 0;

	inline void AddRef() { IncrementReferenceCount(); }
	inline void Release() { DecrementReferenceCount(); }

	// Used to modify the texture bits (procedural textures only)
	virtual void SetTextureRegenerator(void *pTextureRegen, bool releaseExisting = true) = 0;

	// Reconstruct the texture bits in HW memory

	// If rect is not specified, reconstruct all bits, otherwise just
	// reconstruct a subrect.
	virtual void Download(void* *pRect = 0) = 0;

	// Uses for stats. . .get the approximate size of the texture in it's current format.
	virtual int GetApproximateVidMemBytes(void) const = 0;

	// Returns true if the texture data couldn't be loaded.
	virtual bool IsError() const = 0;

	// NOTE: Stuff after this is added after shipping HL2.

	// For volume textures
	virtual bool IsVolumeTexture() const = 0;
	virtual int GetMappingDepth() const = 0;
	virtual int GetActualDepth() const = 0;

	virtual ImageFormat GetImageFormat() const = 0;

	// Various information about the texture
	virtual bool IsRenderTarget() const = 0;
	virtual bool IsCubeMap() const = 0;
	virtual bool IsNormalMap() const = 0;
	virtual bool IsProcedural() const = 0;

	virtual void DeleteIfUnreferenced() = 0;

#if defined( _X360 )
	virtual bool ClearTexture(int r, int g, int b, int a) = 0;
	virtual bool CreateRenderTargetSurface(int width, int height, ImageFormat format, bool bSameAsTexture, RTMultiSampleCount360_t multiSampleCount = RT_MULTISAMPLE_NONE) = 0;
#endif

	// swap everything except the name with another texture
	virtual void SwapContents(ITexture *pOther) = 0;

	// Retrieve the vtf flags mask
	virtual unsigned int GetFlags(void) const = 0;

	// Force LOD override (automatically downloads the texture)
	virtual void ForceLODOverride(int iNumLodsOverrideUpOrDown) = 0;

	// Force exclude override (automatically downloads the texture)
	virtual void ForceExcludeOverride(int iExcludeOverride) = 0;
};
class IMaterialVar
{
public:
	typedef unsigned long FourCC;

protected:
	// base data and accessors
	char* m_pStringVal;
	int m_intVal;
	Vector4D m_VecVal;

	// member data. total = 4 bytes
	uint8 m_Type : 4;
	uint8 m_nNumVectorComps : 3;
	uint8 m_bFakeMaterialVar : 1;
	uint8 m_nTempIndex;
	CUtlSymbol m_Name;

public:
	// class factory methods
	static IMaterialVar* Create(IMaterial* pMaterial, char const* pKey, VMatrix const& matrix);
	static IMaterialVar* Create(IMaterial* pMaterial, char const* pKey, char const* pVal);
	static IMaterialVar* Create(IMaterial* pMaterial, char const* pKey, float* pVal, int numcomps);
	static IMaterialVar* Create(IMaterial* pMaterial, char const* pKey, float val);
	static IMaterialVar* Create(IMaterial* pMaterial, char const* pKey, int val);
	static IMaterialVar* Create(IMaterial* pMaterial, char const* pKey);
	static void Destroy(IMaterialVar* pVar);
	static MaterialVarSym_t	GetSymbol(char const* pName);
	static MaterialVarSym_t	FindSymbol(char const* pName);
	static bool SymbolMatches(char const* pName, MaterialVarSym_t symbol);
	static void DeleteUnreferencedTextures(bool enable);

	virtual ITexture		*GetTextureValue(void) = 0;

	virtual char const *	GetName(void) const = 0;
	virtual MaterialVarSym_t	GetNameAsSymbol() const = 0;

	virtual void			SetFloatValue(float val) = 0;

	virtual void			SetIntValue(int val) = 0;

	virtual void			SetStringValue(char const *val) = 0;
	virtual char const *	GetStringValue(void) const = 0;

	// Use FourCC values to pass app-defined data structures between
	// the proxy and the shader. The shader should ignore the data if
	// its FourCC type not correct.	
	virtual void			SetFourCCValue(FourCC type, void *pData) = 0;
	virtual void			GetFourCCValue(FourCC *type, void **ppData) = 0;

	// Vec (dim 2-4)
	virtual void			SetVecValue(float const* val, int numcomps) = 0;
	virtual void			SetVecValue(float x, float y) = 0;
	virtual void			SetVecValue(float x, float y, float z) = 0;
	virtual void			SetVecValue(float x, float y, float z, float w) = 0;
	virtual void			GetLinearVecValue(float *val, int numcomps) const = 0;

	// revisit: is this a good interface for textures?
	virtual void			SetTextureValue(ITexture *) = 0;

	virtual IMaterial *		GetMaterialValue(void) = 0;
	virtual void			SetMaterialValue(IMaterial *) = 0;

	virtual bool			IsDefined() const = 0;
	virtual void			SetUndefined() = 0;

	// Matrix
	virtual void			SetMatrixValue(VMatrix const& matrix) = 0;
	virtual const VMatrix  &GetMatrixValue() = 0;
	virtual bool			MatrixIsIdentity() const = 0;

	// Copy....
	virtual void			CopyFrom(IMaterialVar *pMaterialVar) = 0;

	virtual void			SetValueAutodetectType(char const *val) = 0;

	virtual IMaterial *		GetOwningMaterial() = 0;

	//set just 1 component
	virtual void			SetVecComponentValue(float fVal, int nComponent) = 0;

protected:
	virtual int				GetIntValueInternal(void) const = 0;
	virtual float			GetFloatValueInternal(void) const = 0;
	virtual float const*	GetVecValueInternal() const = 0;
	virtual void			GetVecValueInternal(float *val, int numcomps) const = 0;
	virtual int				VectorSizeInternal() const = 0;

public:
	FORCEINLINE MaterialVarType_t GetType(void) const
	{
		return (MaterialVarType_t)m_Type;
	}

	FORCEINLINE bool IsTexture() const
	{
		return m_Type == MATERIAL_VAR_TYPE_TEXTURE;
	}

	FORCEINLINE operator ITexture*()
	{
		return GetTextureValue();
	}

	// NOTE: Fast methods should only be called in thread-safe situations
	FORCEINLINE int GetIntValueFast(void) const
	{
		// Set methods for float and vector update this
		return m_intVal;
	}

	FORCEINLINE float GetFloatValueFast(void) const
	{
		return m_VecVal[0];
	}

	FORCEINLINE float const* GetVecValueFast() const
	{
		return m_VecVal.Base();
	}

	FORCEINLINE void GetVecValueFast(float *val, int numcomps) const
	{
		Assert((numcomps >0) && (numcomps <= 4));
		for (int i = 0; i < numcomps; i++)
		{
			val[i] = m_VecVal[i];
		}
	}

	FORCEINLINE int VectorSizeFast() const
	{
		return m_nNumVectorComps;
	}

#ifdef FAST_MATERIALVAR_ACCESS
	FORCEINLINE int GetIntValue(void) const
	{
		return GetIntValueFast();
	}

	FORCEINLINE float GetFloatValue(void) const
	{
		return GetFloatValueFast();
	}

	FORCEINLINE float const* GetVecValue() const
	{
		return GetVecValueFast();
	}

	FORCEINLINE void GetVecValue(float *val, int numcomps) const
	{
		GetVecValueFast(val, numcomps);
	}

	FORCEINLINE int VectorSize() const
	{
		return VectorSizeFast();
	}
#else // !FAST_MATERIALVAR_ACCESS
	FORCEINLINE int GetIntValue(void) const
	{
		return GetIntValueInternal();
	}

	FORCEINLINE float GetFloatValue(void) const
	{
		return GetFloatValueInternal();
	}

	FORCEINLINE float const* GetVecValue() const
	{
		return GetVecValueInternal();
	}

	FORCEINLINE void GetVecValue(float *val, int numcomps) const
	{
		return GetVecValueInternal(val, numcomps);
	}

	FORCEINLINE int VectorSize() const
	{
		return VectorSizeInternal();
	}
#endif

private:
	FORCEINLINE void SetTempIndex(int nIndex)
	{
		m_nTempIndex = nIndex;
	}

	friend void EnableThreadedMaterialVarAccess(bool bEnable, IMaterialVar **ppParams, int nVarCount);
};
typedef uint64 VertexFormat_t;
enum MaterialPropertyTypes_t
{
	MATERIAL_PROPERTY_NEEDS_LIGHTMAP = 0,					// bool
	MATERIAL_PROPERTY_OPACITY,								// int (enum MaterialPropertyOpacityTypes_t)
	MATERIAL_PROPERTY_REFLECTIVITY,							// vec3_t
	MATERIAL_PROPERTY_NEEDS_BUMPED_LIGHTMAPS				// bool
};
enum VertexFormatFlags_t
{
	// Indicates an uninitialized VertexFormat_t value
	VERTEX_FORMAT_INVALID = 0xFFFFFFFF,

	VERTEX_POSITION = 0x0001,
	VERTEX_NORMAL = 0x0002,
	VERTEX_COLOR = 0x0004,
	VERTEX_SPECULAR = 0x0008,

	VERTEX_TANGENT_S = 0x0010,
	VERTEX_TANGENT_T = 0x0020,
	VERTEX_TANGENT_SPACE = VERTEX_TANGENT_S | VERTEX_TANGENT_T,

	// Indicates we're using wrinkle
	VERTEX_WRINKLE = 0x0040,

	// Indicates we're using bone indices
	VERTEX_BONE_INDEX = 0x0080,

	// Indicates this expects a color stream on stream 1
	VERTEX_COLOR_STREAM_1 = 0x0100,

	// Indicates this format shouldn't be bloated to cache align it
	// (only used for VertexUsage)
	VERTEX_FORMAT_USE_EXACT_FORMAT = 0x0200,

	// Indicates that compressed vertex elements are to be used (see also VertexCompressionType_t)
	VERTEX_FORMAT_COMPRESSED = 0x400,

	// Position or normal (if present) should be 4D not 3D
	VERTEX_FORMAT_PAD_POS_NORM = 0x800,

	// Update this if you add or remove bits...
	VERTEX_LAST_BIT = 11,

	VERTEX_BONE_WEIGHT_BIT = VERTEX_LAST_BIT + 1,
	USER_DATA_SIZE_BIT = VERTEX_LAST_BIT + 4,
	TEX_COORD_SIZE_BIT = VERTEX_LAST_BIT + 7,

	VERTEX_BONE_WEIGHT_MASK = (0x7 << VERTEX_BONE_WEIGHT_BIT),
	USER_DATA_SIZE_MASK = (0x7 << USER_DATA_SIZE_BIT),

	VERTEX_FORMAT_FIELD_MASK = 0x0FF,

	// If everything is off, it's an unknown vertex format
	VERTEX_FORMAT_UNKNOWN = 0,
};

class IMaterial
{
public:
	// Get the name of the material.  This is a full path to 
	// the vmt file starting from "hl2/materials" (or equivalent) without
	// a file extension.
	virtual const char*	GetName() const = 0;
	virtual const char*	GetTextureGroupName() const = 0;

	// Get the preferred size/bitDepth of a preview image of a material.
	// This is the sort of image that you would use for a thumbnail view
	// of a material, or in WorldCraft until it uses materials to render.
	// separate this for the tools maybe
	virtual PreviewImageRetVal_t GetPreviewImageProperties(int *width, int *height, ImageFormat *imageFormat, bool* isTranslucent) const = 0;

	// Get a preview image at the specified width/height and bitDepth.
	// Will do resampling if necessary.(not yet!!! :) )
	// Will do color format conversion. (works now.)
	virtual PreviewImageRetVal_t GetPreviewImage(unsigned char *data, int width, int height, ImageFormat imageFormat) const = 0;
	//
	virtual int				GetMappingWidth() = 0;
	virtual int				GetMappingHeight() = 0;
	virtual int				GetNumAnimationFrames() = 0;

	// For material subrects (material pages).  Offset(u,v) and scale(u,v) are normalized to texture.
	virtual bool			InMaterialPage(void) = 0;
	virtual	void			GetMaterialOffset(float *pOffset) = 0;
	virtual void			GetMaterialScale(float *pScale) = 0;
	virtual IMaterial*		GetMaterialPage(void) = 0;

	// find a vmt variable.
	// This is how game code affects how a material is rendered.
	// The game code must know about the params that are used by
	// the shader for the material that it is trying to affect.
	virtual IMaterialVar *	FindVar(const char *varName, bool *found, bool complain = true) = 0;

	// The user never allocates or deallocates materials.  Reference counting is
	// used instead.  Garbage collection is done upon a call to 
	// IMaterialSystem::UncacheUnusedMaterials.
	virtual void			IncrementReferenceCount(void) = 0;
	virtual void			DecrementReferenceCount(void) = 0;

	inline void AddRef() { IncrementReferenceCount(); }
	inline void Release() { DecrementReferenceCount(); }

	// Each material is assigned a number that groups it with like materials
	// for sorting in the application.
	virtual int 			GetEnumerationID(void) const = 0;
	virtual void			GetLowResColorSample(float s, float t, float *color) const = 0;

	// This computes the state snapshots for this material
	virtual void			RecomputeStateSnapshots() = 0;

	// Are we translucent?
	virtual bool			IsTranslucent() = 0;

	// Are we alphatested?
	virtual bool			IsAlphaTested() = 0;

	// Are we vertex lit?
	virtual bool			IsVertexLit() = 0;

	// Gets the vertex format
	virtual VertexFormat_t	GetVertexFormat() const = 0;

	// returns true if this material uses a material proxy
	virtual bool			HasProxy(void) const = 0;
	virtual bool			UsesEnvCubemap(void) = 0;
	virtual bool			NeedsTangentSpace(void) = 0;
	virtual bool			NeedsPowerOfTwoFrameBufferTexture(bool bCheckSpecificToThisFrame = true) = 0;
	virtual bool			NeedsFullFrameBufferTexture(bool bCheckSpecificToThisFrame = true) = 0;

	// returns true if the shader doesn't do skinning itself and requires
	// the data that is sent to it to be preskinned.
	virtual bool			NeedsSoftwareSkinning(void) = 0;

	// Apply constant color or alpha modulation
	virtual void			AlphaModulate(float alpha) = 0;
	virtual void			ColorModulate(float r, float g, float b) = 0;

	// Material Var flags...
	virtual void			SetMaterialVarFlag(MaterialVarFlags_t flag, bool on) = 0;
	virtual bool			GetMaterialVarFlag(MaterialVarFlags_t flag) const = 0;

	// Gets material reflectivity
	virtual void			GetReflectivity(Vector& reflect) = 0;

	// Gets material property flags
	virtual bool			GetPropertyFlag(MaterialPropertyTypes_t type) = 0;

	// Is the material visible from both sides?
	virtual bool			IsTwoSided() = 0;

	// Sets the shader associated with the material
	virtual void			SetShader(const char *pShaderName) = 0;

	// Can't be const because the material might have to precache itself.
	virtual int				GetNumPasses(void) = 0;

	// Can't be const because the material might have to precache itself.
	virtual int				GetTextureMemoryBytes(void) = 0;

	// Meant to be used with materials created using CreateMaterial
	// It updates the materials to reflect the current values stored in the material vars
	virtual void			Refresh() = 0;

	// GR - returns true is material uses lightmap alpha for blending
	virtual bool			NeedsLightmapBlendAlpha(void) = 0;

	// returns true if the shader doesn't do lighting itself and requires
	// the data that is sent to it to be prelighted
	virtual bool			NeedsSoftwareLighting(void) = 0;

	// Gets at the shader parameters
	virtual int				ShaderParamCount() const = 0;
	virtual IMaterialVar**	GetShaderParams(void) = 0;

	// Returns true if this is the error material you get back from IMaterialSystem::FindMaterial if
	// the material can't be found.
	virtual bool			IsErrorMaterial() const = 0;
	virtual void			Unused() = 0;

	// Gets the current alpha modulation
	virtual float			GetAlphaModulation() = 0;

	virtual void			GetColorModulation(float *r, float *g, float *b) = 0;

	// Is this translucent given a particular alpha modulation?
	virtual bool			IsTranslucentUnderModulation(float fAlphaModulation = 1.0f) const = 0;

	// fast find that stores the index of the found var in the string table in local cache
	virtual IMaterialVar *	FindVarFast(char const *pVarName, unsigned int *pToken) = 0;

	// Sets new VMT shader parameters for the material
	virtual void			SetShaderAndParams(KeyValues *pKeyValues) = 0;
	virtual const char *	GetShaderName() const = 0;
	virtual void			DeleteIfUnreferenced() = 0;
	virtual bool			IsSpriteCard() = 0;
	virtual void			CallBindProxy(void *proxyData) = 0;
	virtual void			RefreshPreservingMaterialVars() = 0;
	virtual bool			WasReloadedFromWhitelist() = 0;
	virtual bool			SetTempExcluded(bool bSet, int nExcludedDimensionLimit) = 0;
	virtual int				GetReferenceCount() const = 0;
};

inline bool IsErrorMaterial(IMaterial *pMat)
{
	return !pMat || pMat->IsErrorMaterial();
}

// Vertex stream specifications
struct VertexStreamSpec_t
{
	enum StreamSpec_t
	{
		STREAM_DEFAULT,		// stream 0: with position, normal, etc.
		STREAM_SPECULAR1,	// stream 1: following specular vhv lighting
		STREAM_FLEXDELTA,	// stream 2: flex deltas
		STREAM_MORPH,		// stream 3: morph
		STREAM_UNIQUE_A,	// unique stream 4
		STREAM_UNIQUE_B,	// unique stream 5
		STREAM_UNIQUE_C,	// unique stream 6
		STREAM_UNIQUE_D,	// unique stream 7
		STREAM_SUBDQUADS,	// stream 8: quad buffer for subd's
	};

	enum
	{
		MAX_UNIQUE_STREAMS = 4
	};

	VertexFormatFlags_t iVertexDataElement;
	StreamSpec_t iStreamSpec;
};

inline VertexStreamSpec_t * FindVertexStreamSpec(VertexFormat_t iElement, VertexStreamSpec_t *arrVertexStreamSpec)
{
	for (; arrVertexStreamSpec &&
		arrVertexStreamSpec->iVertexDataElement != VERTEX_FORMAT_UNKNOWN;
		++arrVertexStreamSpec)
	{
		if (arrVertexStreamSpec->iVertexDataElement == iElement)
			return arrVertexStreamSpec;
	}
	return NULL;
}

//-----------------------------------------------------------------------------
// Forward declarations
//-----------------------------------------------------------------------------
class CViewSetup;
class CEngineSprite;
class IClientEntity;
struct model_t;
class IClientRenderable;
struct colorVec
{
	unsigned r, g, b, a;
};
typedef int SideType;
#define	SIDE_FRONT	0
#define	SIDE_BACK	1
#define	SIDE_ON		2

#define VP_EPSILON	0.01f
class VPlane
{
public:
	VPlane();
	VPlane(const Vector &vNormal, vec_t dist);

	void		Init(const Vector &vNormal, vec_t dist);

	// Return the distance from the point to the plane.
	vec_t		DistTo(const Vector &vVec) const;

	// Copy.
	VPlane&		operator=(const VPlane &thePlane);

	// Returns SIDE_ON, SIDE_FRONT, or SIDE_BACK.
	// The epsilon for SIDE_ON can be passed in.
	SideType	GetPointSide(const Vector &vPoint, vec_t sideEpsilon = VP_EPSILON) const;

	// Returns SIDE_FRONT or SIDE_BACK.
	SideType	GetPointSideExact(const Vector &vPoint) const;

	// Classify the box with respect to the plane.
	// Returns SIDE_ON, SIDE_FRONT, or SIDE_BACK
	SideType	BoxOnPlaneSide(const Vector &vMin, const Vector &vMax) const;

#ifndef VECTOR_NO_SLOW_OPERATIONS
	// Flip the plane.
	VPlane		Flip();

	// Get a point on the plane (normal*dist).
	Vector		GetPointOnPlane() const;

	// Snap the specified point to the plane (along the plane's normal).
	Vector		SnapPointToPlane(const Vector &vPoint) const;
#endif

public:
	Vector		m_Normal;
	vec_t		m_Dist;

#ifdef VECTOR_NO_SLOW_OPERATIONS
private:
	// No copy constructors allowed if we're in optimal mode
	VPlane(const VPlane& vOther);
#endif
};
class VMatrix
{
public:

	VMatrix();
	VMatrix(
		vec_t m00, vec_t m01, vec_t m02, vec_t m03,
		vec_t m10, vec_t m11, vec_t m12, vec_t m13,
		vec_t m20, vec_t m21, vec_t m22, vec_t m23,
		vec_t m30, vec_t m31, vec_t m32, vec_t m33
		);

	// Creates a matrix where the X axis = forward
	// the Y axis = left, and the Z axis = up
	VMatrix(const Vector& forward, const Vector& left, const Vector& up);

	// Construct from a 3x4 matrix
	VMatrix(const matrix3x4& matrix3x4);

	// Set the values in the matrix.
	void		Init(
		vec_t m00, vec_t m01, vec_t m02, vec_t m03,
		vec_t m10, vec_t m11, vec_t m12, vec_t m13,
		vec_t m20, vec_t m21, vec_t m22, vec_t m23,
		vec_t m30, vec_t m31, vec_t m32, vec_t m33
		);


	// Initialize from a 3x4
	void		Init(const matrix3x4& matrix3x4);

	// array access
	inline float* operator[](int i)
	{
		return m[i];
	}

	inline const float* operator[](int i) const
	{
		return m[i];
	}

	// Get a pointer to m[0][0]
	inline float *Base()
	{
		return &m[0][0];
	}

	inline const float *Base() const
	{
		return &m[0][0];
	}

	void		SetLeft(const Vector &vLeft);
	void		SetUp(const Vector &vUp);
	void		SetForward(const Vector &vForward);

	void		GetBasisVectors(Vector &vForward, Vector &vLeft, Vector &vUp) const;
	void		SetBasisVectors(const Vector &vForward, const Vector &vLeft, const Vector &vUp);

	// Get/set the translation.
	Vector &	GetTranslation(Vector &vTrans) const;
	void		SetTranslation(const Vector &vTrans);

	void		PreTranslate(const Vector &vTrans);
	void		PostTranslate(const Vector &vTrans);

	matrix3x4& As3x4();
	const matrix3x4& As3x4() const;
	void		CopyFrom3x4(const matrix3x4 &m3x4);
	void		Set3x4(matrix3x4& matrix3x4) const;

	bool		operator==(const VMatrix& src) const;
	bool		operator!=(const VMatrix& src) const { return !(*this == src); }

#ifndef VECTOR_NO_SLOW_OPERATIONS
	// Access the basis vectors.
	Vector		GetLeft() const;
	Vector		GetUp() const;
	Vector		GetForward() const;
	Vector		GetTranslation() const;
#endif


	// Matrix->vector operations.
public:
	// Multiply by a 3D vector (same as operator*).
	void		V3Mul(const Vector &vIn, Vector &vOut) const;

	// Multiply by a 4D vector.
	void		V4Mul(const Vector4D &vIn, Vector4D &vOut) const;

#ifndef VECTOR_NO_SLOW_OPERATIONS
	// Applies the rotation (ignores translation in the matrix). (This just calls VMul3x3).
	Vector		ApplyRotation(const Vector &vVec) const;

	// Multiply by a vector (divides by w, assumes input w is 1).
	Vector		operator*(const Vector &vVec) const;

	// Multiply by the upper 3x3 part of the matrix (ie: only apply rotation).
	Vector		VMul3x3(const Vector &vVec) const;

	// Apply the inverse (transposed) rotation (only works on pure rotation matrix)
	Vector		VMul3x3Transpose(const Vector &vVec) const;

	// Multiply by the upper 3 rows.
	Vector		VMul4x3(const Vector &vVec) const;

	// Apply the inverse (transposed) transformation (only works on pure rotation/translation)
	Vector		VMul4x3Transpose(const Vector &vVec) const;
#endif


	// Matrix->plane operations.
public:
	// Transform the plane. The matrix can only contain translation and rotation.
	void		TransformPlane(const VPlane &inPlane, VPlane &outPlane) const;

#ifndef VECTOR_NO_SLOW_OPERATIONS
	// Just calls TransformPlane and returns the result.
	VPlane		operator*(const VPlane &thePlane) const;
#endif

	// Matrix->matrix operations.
public:

	VMatrix&	operator=(const VMatrix &mOther);

	// Multiply two matrices (out = this * vm).
	void		MatrixMul(const VMatrix &vm, VMatrix &out) const;

	// Add two matrices.
	const VMatrix& operator+=(const VMatrix &other);

#ifndef VECTOR_NO_SLOW_OPERATIONS
	// Just calls MatrixMul and returns the result.	
	VMatrix		operator*(const VMatrix &mOther) const;

	// Add/Subtract two matrices.
	VMatrix		operator+(const VMatrix &other) const;
	VMatrix		operator-(const VMatrix &other) const;

	// Negation.
	VMatrix		operator-() const;

	// Return inverse matrix. Be careful because the results are undefined 
	// if the matrix doesn't have an inverse (ie: InverseGeneral returns false).
	VMatrix		operator~() const;
#endif

	// Matrix operations.
public:
	// Set to identity.
	void		Identity();

	bool		IsIdentity() const;

	// Setup a matrix for origin and angles.
	void		SetupMatrixOrgAngles(const Vector &origin, const Vector &vAngles);

	// General inverse. This may fail so check the return!
	bool		InverseGeneral(VMatrix &vInverse) const;

	// Does a fast inverse, assuming the matrix only contains translation and rotation.
	void		InverseTR(VMatrix &mRet) const;

	// Usually used for debug checks. Returns true if the upper 3x3 contains
	// unit vectors and they are all orthogonal.
	bool		IsRotationMatrix() const;

#ifndef VECTOR_NO_SLOW_OPERATIONS
	// This calls the other InverseTR and returns the result.
	VMatrix		InverseTR() const;

	// Get the scale of the matrix's basis vectors.
	Vector		GetScale() const;

	// (Fast) multiply by a scaling matrix setup from vScale.
	VMatrix		Scale(const Vector &vScale);

	// Normalize the basis vectors.
	VMatrix		NormalizeBasisVectors() const;

	// Transpose.
	VMatrix		Transpose() const;

	// Transpose upper-left 3x3.
	VMatrix		Transpose3x3() const;
#endif

public:
	// The matrix.
	vec_t		m[4][4];
};

// How many networked area portals do we allow?
#define MAX_AREA_STATE_BYTES		32
#define MAX_AREA_PORTAL_STATE_BYTES 24

// user message max payload size (note, this value is used by the engine, so MODs cannot change it)
#define MAX_USER_MSG_BITS 12
#define MAX_USER_MSG_DATA ( ( 1 << ( MAX_USER_MSG_BITS - 3 ) ) - 1 )
#define MAX_ENTITY_MSG_DATA 255


//-----------------------------------------------------------------------------
// Flags used by DrawWorldLists
//-----------------------------------------------------------------------------
enum
{
	DRAWWORLDLISTS_DRAW_STRICTLYABOVEWATER = 0x001,
	DRAWWORLDLISTS_DRAW_STRICTLYUNDERWATER = 0x002,
	DRAWWORLDLISTS_DRAW_INTERSECTSWATER = 0x004,
	DRAWWORLDLISTS_DRAW_WATERSURFACE = 0x008,
	DRAWWORLDLISTS_DRAW_SKYBOX = 0x010,
	DRAWWORLDLISTS_DRAW_CLIPSKYBOX = 0x020,
	DRAWWORLDLISTS_DRAW_SHADOWDEPTH = 0x040,
	DRAWWORLDLISTS_DRAW_REFRACTION = 0x080,
	DRAWWORLDLISTS_DRAW_REFLECTION = 0x100,
	DRAWWORLDLISTS_DRAW_WORLD_GEOMETRY = 0x200,
	DRAWWORLDLISTS_DRAW_DECALS_AND_OVERLAYS = 0x400,
};
enum
{
	MAT_SORT_GROUP_STRICTLY_ABOVEWATER = 0,
	MAT_SORT_GROUP_STRICTLY_UNDERWATER,
	MAT_SORT_GROUP_INTERSECTS_WATER_SURFACE,
	MAT_SORT_GROUP_WATERSURFACE,

	MAX_MAT_SORT_GROUPS
};
enum
{
	FRUSTUM_RIGHT = 0,
	FRUSTUM_LEFT = 1,
	FRUSTUM_TOP = 2,
	FRUSTUM_BOTTOM = 3,
	FRUSTUM_NEARZ = 4,
	FRUSTUM_FARZ = 5,
	FRUSTUM_NUMPLANES = 6
};

typedef VPlane Frustum[FRUSTUM_NUMPLANES];


//-----------------------------------------------------------------------------
// Leaf index
//-----------------------------------------------------------------------------
typedef unsigned short LeafIndex_t;
enum
{
	INVALID_LEAF_INDEX = (LeafIndex_t)~0
};


//-----------------------------------------------------------------------------
// Describes the leaves to be rendered this view, set by BuildWorldLists

//-----------------------------------------------------------------------------
// NOTE: This is slightly slower on x360 but saves memory
#if 1
struct WorldListLeafData_t
{
	LeafIndex_t	leafIndex;	// 16 bits
	int16	waterData;
	uint16 	firstTranslucentSurface;	// engine-internal list index
	uint16	translucentSurfaceCount;	// count of translucent surfaces+disps
};
#else
struct WorldListLeafData_t
{
	uint32	leafIndex;
	int32	waterData;
	uint32	firstTranslucentSurface;	// engine-internal list index
	uint32	translucentSurfaceCount;	// count of translucent surfaces+disps
};
#endif
struct WorldListInfo_t
{
	int		m_ViewFogVolume;
	int		m_LeafCount;
	bool	m_bHasWater;
	WorldListLeafData_t	*m_pLeafDataList;
};
class IRefCounted
{
public:
	virtual int AddRef() = 0;
	virtual int Release() = 0;
};
class IWorldRenderList : public IRefCounted
{
};

//-----------------------------------------------------------------------------
// Describes the fog volume for a particular point
//-----------------------------------------------------------------------------
struct VisibleFogVolumeInfo_t
{
	int		m_nVisibleFogVolume;
	int		m_nVisibleFogVolumeLeaf;
	bool	m_bEyeInFogVolume;
	float	m_flDistanceToWater;
	float	m_flWaterHeight;
	IMaterial *m_pFogVolumeMaterial;
};


//-----------------------------------------------------------------------------
// Vertex format for brush models
//-----------------------------------------------------------------------------
struct BrushVertex_t
{
	Vector		m_Pos;
	Vector		m_Normal;
	Vector		m_TangentS;
	Vector		m_TangentT;
	Vector2D	m_TexCoord;
	Vector2D	m_LightmapCoord;

private:
	BrushVertex_t(const BrushVertex_t& src);
};

//-----------------------------------------------------------------------------
// Visibility data for area portal culling
//-----------------------------------------------------------------------------
struct VisOverrideData_t
{
	Vector		m_vecVisOrigin;					// The point to to use as the viewpoint for area portal backface cull checks.
	float		m_fDistToAreaPortalTolerance;	// The distance from an area portal before using the full screen as the viewable portion.
};


//-----------------------------------------------------------------------------
// interface for asking about the Brush surfaces from the client DLL
//-----------------------------------------------------------------------------

class IBrushSurface
{
public:
	// Computes texture coordinates + lightmap coordinates given a world position
	virtual void ComputeTextureCoordinate(Vector const& worldPos, Vector2D& texCoord) = 0;
	virtual void ComputeLightmapCoordinate(Vector const& worldPos, Vector2D& lightmapCoord) = 0;

	// Gets the vertex data for this surface
	virtual int  GetVertexCount() const = 0;
	virtual void GetVertexData(BrushVertex_t* pVerts) = 0;

	// Gets at the material properties for this surface
	virtual IMaterial* GetMaterial() = 0;
};


//-----------------------------------------------------------------------------
// interface for installing a new renderer for brush surfaces
//-----------------------------------------------------------------------------

class IBrushRenderer
{
public:
	// Draws the surface; returns true if decals should be rendered on this surface
	virtual bool RenderBrushModelSurface(IClientEntity* pBaseEntity, IBrushSurface* pBrushSurface) = 0;
};


#define MAX_VIS_LEAVES	32
//-----------------------------------------------------------------------------
// Purpose: Interface to client .dll to set up a rendering pass over world
//  The client .dll can call Render multiple times to overlay one or more world
//  views on top of one another
//-----------------------------------------------------------------------------
class IVRenderView
{
public:

	// Draw normal brush model.
	// If pMaterialOverride is non-null, then all the faces of the bmodel will
	// set this material rather than their regular material.
	virtual void			DrawBrushModel(IClientEntity *baseentity, model_t *model, const Vector& origin, const Vector& angles, bool sort) = 0;

	// Draw brush model that has no origin/angles change ( uses identity transform )
	// FIXME, Material proxy IClientEntity *baseentity is unused right now, use DrawBrushModel for brushes with
	//  proxies for now.
	virtual void			DrawIdentityBrushModel(IWorldRenderList *pList, model_t *model) = 0;

	// Mark this dynamic light as having changed this frame ( so light maps affected will be recomputed )
	virtual void			TouchLight(struct dlight_t *light) = 0;
	// Draw 3D Overlays
	virtual void			Draw3DDebugOverlays(void) = 0;
	// Sets global blending fraction
	virtual void			SetBlend(float blend) = 0;
	virtual float			GetBlend(void) = 0;

	// Sets global color modulation
	virtual void			SetColorModulation(float const* blend) = 0;
	virtual void			GetColorModulation(float* blend) = 0;

	// Wrap entire scene drawing
	virtual void			SceneBegin(void) = 0;
	virtual void			SceneEnd(void) = 0;

	// Gets the fog volume for a particular point
	virtual void			GetVisibleFogVolume(const Vector& eyePoint, VisibleFogVolumeInfo_t *pInfo) = 0;

	// Wraps world drawing
	// If iForceViewLeaf is not -1, then it uses the specified leaf as your starting area for setting up area portal culling.
	// This is used by water since your reflected view origin is often in solid space, but we still want to treat it as though
	// the first portal we're looking out of is a water portal, so our view effectively originates under the water.
	virtual IWorldRenderList * CreateWorldList() = 0;

	virtual void			DrawWorldLists(IWorldRenderList *pList, unsigned long flags, float waterZAdjust) = 0;
	virtual void			BuildWorldLists(IWorldRenderList *pList, WorldListInfo_t* pInfo, int iForceFViewLeaf, const VisOverrideData_t* pVisData = NULL, bool bShadowDepth = false, float *pReflectionWaterHeight = NULL) = 0;
	virtual int				GetNumIndicesForWorldLists(IWorldRenderList *pList, unsigned long nFlags) = 0;

	// Optimization for top view
	virtual void			DrawTopView(bool enable) = 0;
	virtual void			TopViewBounds(Vector2D const& mins, Vector2D const& maxs) = 0;

	// Draw lights
	virtual void			DrawLights(void) = 0;
	// FIXME:  This function is a stub, doesn't do anything in the engine right now
	virtual void			DrawMaskEntities(void) = 0;

	// Draw surfaces with alpha, don't call in shadow depth pass
	virtual void			DrawTranslucentSurfaces(IWorldRenderList *pList, int *pSortList, int sortCount, unsigned long flags) = 0;

	// Draw Particles ( just draws the linefine for debugging map leaks )
	virtual void			DrawLineFile(void) = 0;
	// Draw lightmaps
	virtual void			DrawLightmaps(IWorldRenderList *pList, int pageId) = 0;
	// Wraps view render sequence, sets up a view
	virtual void			ViewSetupVis(bool novis, int numorigins, const Vector origin[]) = 0;

	// Return true if any of these leaves are visible in the current PVS.
	virtual bool			AreAnyLeavesVisible(int *leafList, int nLeaves) = 0;

	virtual	void			VguiPaint(void) = 0;
	// Sets up view fade parameters
	virtual void			ViewDrawFade(byte *color, IMaterial *pMaterial) = 0;
	// Sets up the projection matrix for the specified field of view
	virtual void			OLD_SetProjectionMatrix(float fov, float zNear, float zFar) = 0;
	// Determine lighting at specified position
	virtual colorVec		GetLightAtPoint(Vector& pos) = 0;
	// Whose eyes are we looking through?
	virtual int				GetViewEntity(void) = 0;
	virtual bool			IsViewEntity(int entindex) = 0;
	// Get engine field of view setting
	virtual float			GetFieldOfView(void) = 0;
	// 1 == ducking, 0 == not
	virtual unsigned char	**GetAreaBits(void) = 0;

	// Set up fog for a particular leaf
	virtual void			SetFogVolumeState(int nVisibleFogVolume, bool bUseHeightFog) = 0;

	// Installs a brush surface draw override method, null means use normal renderer
	virtual void			InstallBrushSurfaceRenderer(IBrushRenderer* pBrushRenderer) = 0;

	// Draw brush model shadow
	virtual void			DrawBrushModelShadow(IClientRenderable *pRenderable) = 0;

	// Does the leaf contain translucent surfaces?
	virtual	bool			LeafContainsTranslucentSurfaces(IWorldRenderList *pList, int sortIndex, unsigned long flags) = 0;

	virtual bool			DoesBoxIntersectWaterVolume(const Vector &mins, const Vector &maxs, int leafWaterDataID) = 0;

	virtual void			SetAreaState(unsigned char chAreaBits[MAX_AREA_STATE_BYTES], unsigned char chAreaPortalBits[MAX_AREA_PORTAL_STATE_BYTES]) = 0;

	// See i
	virtual void			VGui_Paint(int mode) = 0;
	// Push, pop views (see PushViewFlags_t above for flags)
	virtual void			Push3DView(const CViewSetup &view, int nFlags, void* pRenderTarget, Frustum frustumPlanes) = 0;
	virtual void			Push2DView(const CViewSetup &view, int nFlags, void* pRenderTarget, Frustum frustumPlanes) = 0;
	virtual void			PopView(Frustum frustumPlanes) = 0;
	// Sets the main view
	virtual void			SetMainView(const Vector &vecOrigin, const Vector &angles) = 0;

	enum
	{
		VIEW_SETUP_VIS_EX_RETURN_FLAGS_USES_RADIAL_VIS = 0x00000001
	};

	// Wraps view render sequence, sets up a view
	virtual void			ViewSetupVisEx(bool novis, int numorigins, const Vector origin[], unsigned int &returnFlags) = 0;

	//replaces the current view frustum with a rhyming replacement of your choice
	virtual void			OverrideViewFrustum(Frustum custom) = 0;
	virtual void			DrawBrushModelShadowDepth(IClientEntity *baseentity, model_t *model, const Vector& origin, const Vector& angles, bool bSort) = 0;
	virtual void			UpdateBrushModelLightmap(model_t *model, IClientRenderable *pRenderable) = 0;
	virtual void			BeginUpdateLightmaps(void) = 0;
	virtual void			EndUpdateLightmaps(void) = 0;
	virtual void			OLD_SetOffCenterProjectionMatrix(float fov, float zNear, float zFar, float flAspectRatio, float flBottom, float flTop, float flLeft, float flRight) = 0;
	virtual void			OLD_SetProjectionMatrixOrtho(float left, float top, float right, float bottom, float zNear, float zFar) = 0;
	virtual void			Push3DView(const CViewSetup &view, int nFlags, void* pRenderTarget, Frustum frustumPlanes, void* pDepthTexture) = 0;
	virtual void			GetMatricesForView(const CViewSetup &view, VMatrix *pWorldToView, VMatrix *pViewToProjection, VMatrix *pWorldToProjection, VMatrix *pWorldToPixels) = 0;
};



enum ClearFlags_t
{
	VIEW_CLEAR_COLOR = 0x1,
	VIEW_CLEAR_DEPTH = 0x2,
	VIEW_CLEAR_FULL_TARGET = 0x4,
	VIEW_NO_DRAW = 0x8,
	VIEW_CLEAR_OBEY_STENCIL = 0x10, // Draws a quad allowing stencil test to clear through portals
	VIEW_CLEAR_STENCIL = 0x20,
};

enum StereoEye_t
{
	STEREO_EYE_MONO = 0,
	STEREO_EYE_LEFT = 1,
	STEREO_EYE_RIGHT = 2,
	STEREO_EYE_MAX = 3,
};

enum MotionBlurMode_t
{
	MOTION_BLUR_DISABLE = 1,
	MOTION_BLUR_GAME = 2,			// Game uses real-time inter-frame data
	MOTION_BLUR_SFM = 3				// Use SFM data passed in CViewSetup structure
};

class CViewSetup
{
public:
	CViewSetup()
	{
		m_flAspectRatio = 0.0f;
		// These match mat_dof convars
		m_flNearBlurDepth = 20.0;
		m_flNearFocusDepth = 100.0;
		m_flFarFocusDepth = 250.0;
		m_flFarBlurDepth = 1000.0;
		m_flNearBlurRadius = 10.0;
		m_flFarBlurRadius = 5.0;
		m_nDoFQuality = 0;
		m_bCustomViewMatrix = false;

		//m_bRenderToSubrectOfLargerScreen = false;
		//m_bDoBloomAndToneMapping = true;
		//m_nMotionBlurMode = MOTION_BLUR_GAME;
		//m_bDoDepthOfField = false;
		//m_bHDRTarget = false;
		//m_bOffCenter = false;
		//m_bCacheFullSceneState = false;
		//m_bDrawWorldNormal = false;
		//m_bCullFrontFaces = false;
		//		//m_bUseExplicitViewVector = false;
		//m_bRenderFlashlightDepthTranslucents = false;
	}

	// left side of view window
	int			x, x_old;
	// top side of view window
	int			y, y_old;
	// width of view window
	int			width, width_old;
	// height of view window
	int			height, height_old;
	// the rest are only used by 3D views
	// Orthographic projection?
	bool		m_bOrtho;
	// View-space rectangle for ortho projection.
	float		m_OrthoLeft;
	float		m_OrthoTop;
	float		m_OrthoRight;
	float		m_OrthoBottom;
	bool		m_bCustomViewMatrix; // 0x34
	matrix3x4	m_matCustomViewMatrix; // 0x38
	char		pad_0x68[0x48]; // 0x68
								// horizontal FOV in degrees
	float		fov; //	0xB0
					 // horizontal FOV in degrees for in-view model
	float		fovViewmodel;
	// 3D origin of camera
	Vector		origin;
	// heading of camera (pitch, yaw, roll)
	Vector		angles;
	// local Z coordinate of near plane of camera
	float		zNear;
	// local Z coordinate of far plane of camera
	float		zFar;
	// local Z coordinate of near plane of camera ( when rendering view model )
	float		zNearViewmodel;
	// local Z coordinate of far plane of camera ( when rendering view model )
	float		zFarViewmodel;
	// The aspect ratio to use for computing the perspective projection matrix
	// (0.0f means use the viewport)//
	float		m_flAspectRatio;//ASpec ratio
	// Camera settings to control depth of field
	float		m_flNearBlurDepth;
	float		m_flNearFocusDepth;
	float		m_flFarFocusDepth;
	float		m_flFarBlurDepth;
	float		m_flNearBlurRadius;
	float		m_flFarBlurRadius;
	int			m_nDoFQuality;
	// Camera settings to control motion blur
	MotionBlurMode_t	m_nMotionBlurMode;
	float		m_flShutterTime;				// In seconds
	Vector		m_vShutterOpenPosition;			// Start of frame or "shutter open"
	Vector		m_shutterOpenAngles;			//
	Vector		m_vShutterClosePosition;		// End of frame or "shutter close"
	Vector		m_shutterCloseAngles;			// 
												// Controls for off-center projection (needed for poster rendering)
	float		m_flOffCenterTop;
	float		m_flOffCenterBottom;
	float		m_flOffCenterLeft;
	float		m_flOffCenterRight;
	int			m_EdgeBlur; // 0x148
							//end
							//bool		m_bOffCenter:1;
							//// set to true if this is to draw into a subrect of the larger screen
							//// this really is a hack, but no more than the rest of the way this class is used
							//bool		m_bRenderToSubrectOfLargerScreen:1;
							//// Controls that the SFM needs to tell the engine when to do certain post-processing steps
							//bool		m_bDoBloomAndToneMapping:1;
							//bool		m_bDoDepthOfField:1;
							//bool		m_bHDRTarget:1;
							//bool		m_bDrawWorldNormal:1;
							//bool		m_bCullFrontFaces:1;
							//// Cached mode for certain full-scene per-frame varying state such as sun entity coverage
							//bool		m_bCacheFullSceneState:1;
							//bool		m_bRenderFlashlightDepthTranslucents:1;

}; // size = 0x14C = 332