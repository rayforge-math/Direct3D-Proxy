/*
    Undocumented function prototypes were determined using IDA Pro and the following references:
        https://github.com/doitsujin/dxvk/blob/master/src/d3d11/d3d11_main.cpp
        https://github.com/bo3b/3Dmigoto/blob/master/DirectX11/D3D11Wrapper.cpp
        https://chromium.googlesource.com/external/p3/regal/+/cass/src/apitrace/wrappers/d3d11stubs.cpp
*/

#include "d3d11/d3d11_impl.h"
#include "d3d11/d3d11_hook.h"

namespace d3d11 {

    extern "C" {

        // Creates an instance of IDirect3DDevice from an IDXGIDevice.
        // https://msdn.microsoft.com/en-us/library/windows/apps/dn895087.aspx
        HRESULT WINAPI CreateDirect3D11DeviceFromDXGIDevice_(_In_ IDXGIDevice* dxgiDevice, _Out_ IInspectable** graphicsDevice)
        {
            HRESULT result = CreateDirect3D11DeviceFromDXGIDevice_t(dx_func(CreateDirect3D11DeviceFromDXGIDevice_i))(dxgiDevice, graphicsDevice);
            return result;
        }

        // Creates an instance of IDirect3DSurface from an IDXGISurface.
        // https://msdn.microsoft.com/en-us/library/windows/apps/dn895088.aspx
        HRESULT WINAPI CreateDirect3D11SurfaceFromDXGISurface_(_In_ IDXGISurface* dxgiSurface, _Out_ IInspectable** graphicsSurface)
        {
            HRESULT result = CreateDirect3D11SurfaceFromDXGISurface_t(dx_func(CreateDirect3D11SurfaceFromDXGISurface_i))(dxgiSurface, graphicsSurface);
            return result;
        }

        HRESULT WINAPI D3D11CoreCreateDevice_(
            IDXGIFactory* pFactory,
            IDXGIAdapter* pAdapter,
            UINT Flags,
            const D3D_FEATURE_LEVEL* pFeatureLevels,
            UINT FeatureLevels,
            ID3D11Device** ppDevice)
        {
            HRESULT result = D3D11CoreCreateDevice_t(dx_func(D3D11CoreCreateDevice_i))(pFactory, pAdapter, Flags, pFeatureLevels, FeatureLevels, ppDevice);
            return result;
        }

        HRESULT WINAPI D3D11CoreCreateLayeredDevice_(
            const void* unknown0,
            DWORD unknown1,
            const void* unknown2,
            REFIID riid,
            void** ppvObj)
        {
            HRESULT result = D3D11CoreCreateLayeredDevice_t(dx_func(D3D11CoreCreateLayeredDevice_i))(unknown0, unknown1, unknown2, riid, ppvObj);
            return result;
        }

        SIZE_T WINAPI D3D11CoreGetLayeredDeviceSize_(const void* unknown0, DWORD unknown1)
        {
            SIZE_T result = D3D11CoreGetLayeredDeviceSize_t(dx_func(D3D11CoreGetLayeredDeviceSize_i))(unknown0, unknown1);
            return result;
        }

        HRESULT WINAPI D3D11CoreRegisterLayers_(const void* unknown0, DWORD unknown1)
        {
            HRESULT result = D3D11CoreRegisterLayers_t(dx_func(D3D11CoreRegisterLayers_i))(unknown0, unknown1);
            return result;
        }

        // Creates a device that represents the display adapter.
        // https://msdn.microsoft.com/en-us/library/windows/desktop/ff476082%28v=vs.85%29.aspx?f=255&MSPPError=-2147217396
        HRESULT WINAPI D3D11CreateDevice_(
            _In_opt_ IDXGIAdapter* pAdapter,
            D3D_DRIVER_TYPE DriverType,
            HMODULE Software,
            UINT Flags,
            _In_opt_ const D3D_FEATURE_LEVEL* pFeatureLevels,
            UINT FeatureLevels,
            UINT SDKVersion,
            _Out_opt_ ID3D11Device** ppDevice,
            _Out_opt_ D3D_FEATURE_LEVEL* pFeatureLevel,
            _Out_opt_ ID3D11DeviceContext** ppImmediateContext)
        {
            HRESULT result = D3D11CreateDevice_t(dx_func(D3D11CreateDevice_i))(pAdapter, DriverType, Software, Flags, pFeatureLevels, FeatureLevels, SDKVersion, ppDevice, pFeatureLevel, ppImmediateContext);
            return result;
        }

        // Creates a device that represents the display adapter and a swap chain used for rendering.
        // https://msdn.microsoft.com/en-us/library/windows/desktop/ff476083(v=vs.85).aspx
        HRESULT WINAPI D3D11CreateDeviceAndSwapChain_(
            _In_opt_ IDXGIAdapter* pAdapter,
            D3D_DRIVER_TYPE DriverType,
            HMODULE Software,
            UINT Flags,
            _In_opt_ const D3D_FEATURE_LEVEL* pFeatureLevels,
            UINT FeatureLevels,
            UINT SDKVersion,
            _In_opt_ const DXGI_SWAP_CHAIN_DESC* pSwapChainDesc,
            _Out_opt_ IDXGISwapChain** ppSwapChain,
            _Out_opt_ ID3D11Device** ppDevice,
            _Out_opt_ D3D_FEATURE_LEVEL* pFeatureLevel,
            _Out_opt_ ID3D11DeviceContext** ppImmediateContext)
        {
            HRESULT result = D3D11CreateDeviceAndSwapChain_t(dx_func(D3D11CreateDeviceAndSwapChain_i))(pAdapter, DriverType, Software, Flags, pFeatureLevels, FeatureLevels, SDKVersion, pSwapChainDesc, ppSwapChain, ppDevice, pFeatureLevel, ppImmediateContext);
            return result;
        }

        HRESULT WINAPI D3D11CreateDeviceForD3D12_(
            IUnknown* pDevice,
            UINT Flags,
            const D3D_FEATURE_LEVEL* pFeatureLevels,
            UINT FeatureLevels,
            UINT NumQueues,
            UINT NodeMask,
            ID3D11Device** ppDevice,
            ID3D11DeviceContext** ppImmediateContext,
            D3D_FEATURE_LEVEL* pChosenFeatureLevel)
        {
            HRESULT result = D3D11CreateDeviceForD3D12_t(dx_func(D3D11CreateDeviceForD3D12_i))(pDevice, Flags, pFeatureLevels, FeatureLevels, NumQueues, NodeMask, ppDevice, ppImmediateContext, pChosenFeatureLevel);
            return result;
        }

        HRESULT WINAPI D3D11On12CreateDevice_(
            _In_ IUnknown* pDevice,
            UINT Flags,
            _In_opt_ const D3D_FEATURE_LEVEL* pFeatureLevels,
            UINT FeatureLevels,
            _In_opt_ IUnknown* ppCommandQueues,
            UINT NumQueues,
            UINT NodeMask,
            _Out_opt_ ID3D11Device** ppDevice,
            _Out_opt_ ID3D11DeviceContext** ppImmediateContext,
            _Out_opt_ D3D_FEATURE_LEVEL* pChosenFeatureLevel)
        {
            HRESULT result = D3D11On12CreateDevice_t(dx_func(D3D11On12CreateDevice_i))(pDevice, Flags, pFeatureLevels, FeatureLevels, ppCommandQueues, NumQueues, NodeMask, ppDevice, ppImmediateContext, pChosenFeatureLevel);
            return result;
        }

        // Closes a graphics adapter that was previously opened by using the D3DKMTOpenAdapterFromHdc function.
        // https://docs.microsoft.com/en-us/windows-hardware/drivers/ddi/content/d3dkmthk/nf-d3dkmthk-d3dkmtcloseadapter
        //NTSTATUS APIENTRY D3DKMTCloseAdapter_(const D3DKMT_CLOSEADAPTER* pAdapter)
        HRESULT WINAPI D3DKMTCloseAdapter_()
        {
            auto fn = dx_func(D3DKMTCloseAdapter_i);
            HRESULT result = fn ? D3DKMTCloseAdapter_t(fn)() : E_NOTIMPL;
            return result;
        }

        // Creates allocations of system or video memory.
        // https://docs.microsoft.com/en-us/windows-hardware/drivers/ddi/content/d3dkmthk/nf-d3dkmthk-d3dkmtcreateallocation
        //NTSTATUS APIENTRY D3DKMTCreateAllocation_(D3DKMT_CREATEALLOCATION* Arg1)
        HRESULT WINAPI D3DKMTCreateAllocation_()
        {
            auto fn = dx_func(D3DKMTCreateAllocation_i);
            HRESULT result = fn ? D3DKMTCreateAllocation_t(fn)() : E_NOTIMPL;
            return result;
        }

        // Creates a kernel-mode device context.
        // https://docs.microsoft.com/en-us/windows-hardware/drivers/ddi/content/d3dkmthk/nf-d3dkmthk-d3dkmtcreatecontext
        //NTSTATUS APIENTRY D3DKMTCreateContext_(D3DKMT_CREATECONTEXT* Arg1)
        HRESULT WINAPI D3DKMTCreateContext_()
        {
            auto fn = dx_func(D3DKMTCreateContext_i);
            HRESULT result = fn ? D3DKMTCreateContext_t(fn)() : E_NOTIMPL;
            return result;
        }

        // Creates a kernel-mode device context.
        // https://docs.microsoft.com/en-us/windows-hardware/drivers/ddi/content/d3dkmthk/nf-d3dkmthk-d3dkmtcreatedevice
        //NTSTATUS APIENTRY D3DKMTCreateDevice_(D3DKMT_CREATEDEVICE* Arg1)
        HRESULT WINAPI D3DKMTCreateDevice_()
        {
            auto fn = dx_func(D3DKMTCreateDevice_i);
            HRESULT result = fn ? D3DKMTCreateDevice_t(fn)() : E_NOTIMPL;
            return result;
        }

        // Creates a kernel-mode synchronization object.
        // https://docs.microsoft.com/en-us/windows-hardware/drivers/ddi/content/d3dkmthk/nf-d3dkmthk-d3dkmtcreatesynchronizationobject
        //NTSTATUS APIENTRY D3DKMTCreateSynchronizationObject_(D3DKMT_CREATESYNCHRONIZATIONOBJECT* Arg1)
        HRESULT WINAPI D3DKMTCreateSynchronizationObject_()
        {
            auto fn = dx_func(D3DKMTCreateSynchronizationObject_i);
            HRESULT result = fn ? D3DKMTCreateSynchronizationObject_t(fn)() : E_NOTIMPL;
            return result;
        }

        // Releases a resource, a list of allocations, or both.
        // https://docs.microsoft.com/en-us/windows-hardware/drivers/ddi/content/d3dkmthk/nf-d3dkmthk-d3dkmtdestroyallocation
        //NTSTATUS APIENTRY D3DKMTDestroyAllocation_(const D3DKMT_DESTROYALLOCATION* Arg1)
        HRESULT WINAPI D3DKMTDestroyAllocation_()
        {
            auto fn = dx_func(D3DKMTDestroyAllocation_i);
            HRESULT result = fn ? D3DKMTDestroyAllocation_t(fn)() : E_NOTIMPL;
            return result;
        }

        // Releases a kernel-mode device context.
        // https://docs.microsoft.com/en-us/windows-hardware/drivers/ddi/content/d3dkmthk/nf-d3dkmthk-d3dkmtdestroycontext
        //NTSTATUS APIENTRY D3DKMTDestroyContext_(const D3DKMT_DESTROYCONTEXT* Arg1)
        HRESULT WINAPI D3DKMTDestroyContext_()
        {
            auto fn = dx_func(D3DKMTDestroyContext_i);
            HRESULT result = fn ? D3DKMTDestroyContext_t(fn)() : E_NOTIMPL;
            return result;
        }

        // Releases a kernel-mode device context.
        // https://docs.microsoft.com/en-us/windows-hardware/drivers/ddi/content/d3dkmthk/nf-d3dkmthk-d3dkmtdestroydevice
        //NTSTATUS APIENTRY D3DKMTDestroyDevice_(const D3DKMT_DESTROYDEVICE* Arg1)
        HRESULT WINAPI D3DKMTDestroyDevice_()
        {
            auto fn = dx_func(D3DKMTDestroyDevice_i);
            HRESULT result = fn ? D3DKMTDestroyDevice_t(fn)() : E_NOTIMPL;
            return result;
        }

        // Destroys a kernel-mode synchronization object.
        // https://docs.microsoft.com/en-us/windows-hardware/drivers/ddi/content/d3dkmthk/nf-d3dkmthk-d3dkmtdestroysynchronizationobject
        //NTSTATUS APIENTRY D3DKMTDestroySynchronizationObject_(const D3DKMT_DESTROYSYNCHRONIZATIONOBJECT* Arg1)
        HRESULT WINAPI D3DKMTDestroySynchronizationObject_()
        {
            auto fn = dx_func(D3DKMTDestroySynchronizationObject_i);
            HRESULT result = fn ? D3DKMTDestroySynchronizationObject_t(fn)() : E_NOTIMPL;
            return result;
        }

        // Exchanges information with the display miniport driver.
        // https://docs.microsoft.com/en-us/windows-hardware/drivers/ddi/content/d3dkmthk/nf-d3dkmthk-d3dkmtescape
        //NTSTATUS APIENTRY D3DKMTEscape_(const D3DKMT_ESCAPE* Arg1)
        HRESULT WINAPI D3DKMTEscape_()
        {
            auto fn = dx_func(D3DKMTEscape_i);
            HRESULT result = fn ? D3DKMTEscape_t(fn)() : E_NOTIMPL;
            return result;
        }

        // Retrieves the scheduling priority for a device context.
        // https://docs.microsoft.com/en-us/windows-hardware/drivers/ddi/content/d3dkmthk/nf-d3dkmthk-d3dkmtgetcontextschedulingpriority
        //NTSTATUS APIENTRY D3DKMTGetContextSchedulingPriority_(D3DKMT_GETCONTEXTSCHEDULINGPRIORITY* Arg1)
        HRESULT WINAPI D3DKMTGetContextSchedulingPriority_()
        {
            auto fn = dx_func(D3DKMTGetContextSchedulingPriority_i);
            HRESULT result = fn ? D3DKMTGetContextSchedulingPriority_t(fn)() : E_NOTIMPL;
            return result;
        }

        // Retrieves the state of a device.
        // https://docs.microsoft.com/en-us/windows-hardware/drivers/ddi/content/d3dkmthk/nf-d3dkmthk-d3dkmtgetdevicestate
        //NTSTATUS APIENTRY D3DKMTGetDeviceState_(D3DKMT_GETDEVICESTATE* Arg1)
        HRESULT WINAPI D3DKMTGetDeviceState_()
        {
            auto fn = dx_func(D3DKMTGetDeviceState_i);
            HRESULT result = fn ? D3DKMTGetDeviceState_t(fn)() : E_NOTIMPL;
            return result;
        }

        // Retrieves a list of available display modes, including modes with extended format.
        // https://msdn.microsoft.com/en-us/windows/hardware/ff546967(v=vs.100)
        //NTSTATUS APIENTRY D3DKMTGetDisplayModeList_(_Inout_ D3DKMT_GETDISPLAYMODELIST* pData)
        HRESULT WINAPI D3DKMTGetDisplayModeList_()
        {
            auto fn = dx_func(D3DKMTGetDisplayModeList_i);
            HRESULT result = fn ? D3DKMTGetDisplayModeList_t(fn)() : E_NOTIMPL;
            return result;
        }

        // Retrieves a list of multiple-sample methods that are used for an allocation.
        // https://docs.microsoft.com/en-us/windows-hardware/drivers/ddi/content/d3dkmthk/nf-d3dkmthk-d3dkmtgetmultisamplemethodlist
        //NTSTATUS APIENTRY D3DKMTGetMultisampleMethodList_(D3DKMT_GETMULTISAMPLEMETHODLIST* Arg1)
        HRESULT WINAPI D3DKMTGetMultisampleMethodList_()
        {
            auto fn = dx_func(D3DKMTGetMultisampleMethodList_i);
            HRESULT result = fn ? D3DKMTGetMultisampleMethodList_t(fn)() : E_NOTIMPL;
            return result;
        }

        // For system use only.
        // https://docs.microsoft.com/en-us/windows-hardware/drivers/ddi/content/d3dkmthk/nf-d3dkmthk-d3dkmtgetruntimedata
        //NTSTATUS APIENTRY D3DKMTGetRuntimeData_(const D3DKMT_GETRUNTIMEDATA* Arg1)
        HRESULT WINAPI D3DKMTGetRuntimeData_()
        {
            auto fn = dx_func(D3DKMTGetRuntimeData_i);
            HRESULT result = fn ? D3DKMTGetRuntimeData_t(fn)() : E_NOTIMPL;
            return result;
        }

        // Retrieves the global shared handle for the primary surface.
        // https://docs.microsoft.com/en-us/windows-hardware/drivers/ddi/content/d3dkmthk/nf-d3dkmthk-d3dkmtgetsharedprimaryhandle
        //NTSTATUS APIENTRY D3DKMTGetSharedPrimaryHandle_(D3DKMT_GETSHAREDPRIMARYHANDLE* Arg1)
        HRESULT WINAPI D3DKMTGetSharedPrimaryHandle_()
        {
            auto fn = dx_func(D3DKMTGetSharedPrimaryHandle_i);
            HRESULT result = fn ? D3DKMTGetSharedPrimaryHandle_t(fn)() : E_NOTIMPL;
            return result;
        }

        // Locks an entire allocation or specific pages within an allocation.
        // https://docs.microsoft.com/en-us/windows-hardware/drivers/ddi/content/d3dkmthk/nf-d3dkmthk-d3dkmtlock
        //NTSTATUS APIENTRY D3DKMTLock_(D3DKMT_LOCK* Arg1)
        HRESULT WINAPI D3DKMTLock_()
        {
            auto fn = dx_func(D3DKMTLock_i);
            HRESULT result = fn ? D3DKMTLock_t(fn)() : E_NOTIMPL;
            return result;
        }

        // Maps a device context handle (HDC) to a graphics adapter handle and, if the adapter contains multiple monitor outputs, to one of those outputs.
        // https://docs.microsoft.com/en-us/windows-hardware/drivers/ddi/content/d3dkmthk/nf-d3dkmthk-d3dkmtopenadapterfromhdc
        //NTSTATUS APIENTRY D3DKMTOpenAdapterFromHdc_(D3DKMT_OPENADAPTERFROMHDC* Arg1)
        HRESULT WINAPI D3DKMTOpenAdapterFromHdc_()
        {
            auto fn = dx_func(D3DKMTOpenAdapterFromHdc_i);
            HRESULT result = fn ? D3DKMTOpenAdapterFromHdc_t(fn)() : E_NOTIMPL;
            return result;
        }

        // Opens a shared resource.
        // https://technet.microsoft.com/en-us/windows/ff547065%28v=vs.80%29?f=255&MSPPError=-2147217396
        //NTSTATUS APIENTRY D3DKMTOpenResource_(_Inout_ D3DKMT_OPENRESOURCE* pData)
        HRESULT WINAPI D3DKMTOpenResource_()
        {
            auto fn = dx_func(D3DKMTOpenResource_i);
            HRESULT result = fn ? D3DKMTOpenResource_t(fn)() : E_NOTIMPL;
            return result;
        }

        // Submits a present command to the Microsoft DirectX graphics kernel subsystem (Dxgkrnl.sys).
        // https://docs.microsoft.com/en-us/windows-hardware/drivers/ddi/content/d3dkmthk/nf-d3dkmthk-d3dkmtpresent
        //NTSTATUS APIENTRY D3DKMTPresent_(D3DKMT_PRESENT* Arg1)
        HRESULT WINAPI D3DKMTPresent_()
        {
            auto fn = dx_func(D3DKMTPresent_i);
            HRESULT result = fn ? D3DKMTPresent_t(fn)() : E_NOTIMPL;
            return result;
        }

        // Retrieves graphics adapter information.
        // https://msdn.microsoft.com/en-us/windows/ff547100(v=vs.80)
        //NTSTATUS APIENTRY D3DKMTQueryAdapterInfo_(_Inout_ const D3DKMT_QUERYADAPTERINFO* pData)
        HRESULT WINAPI D3DKMTQueryAdapterInfo_()
        {
            auto fn = dx_func(D3DKMTQueryAdapterInfo_i);
            HRESULT result = fn ? D3DKMTQueryAdapterInfo_t(fn)() : E_NOTIMPL;
            return result;
        }

        // Retrieves the residency status of a resource or list of allocations.
        // https://docs.microsoft.com/en-us/windows-hardware/drivers/ddi/content/d3dkmthk/nf-d3dkmthk-d3dkmtqueryallocationresidency
        //NTSTATUS APIENTRY D3DKMTQueryAllocationResidency_(const D3DKMT_QUERYALLOCATIONRESIDENCY* Arg1)
        HRESULT WINAPI D3DKMTQueryAllocationResidency_()
        {
            auto fn = dx_func(D3DKMTQueryAllocationResidency_i);
            HRESULT result = fn ? D3DKMTQueryAllocationResidency_t(fn)() : E_NOTIMPL;
            return result;
        }

        // Retrieves information about a shared resource.
        // https://technet.microsoft.com/en-us/windows/ff547124(v=vs.60)
        //NTSTATUS APIENTRY D3DKMTQueryResourceInfo_(_Inout_ D3DKMT_QUERYRESOURCEINFO* pData)
        HRESULT WINAPI D3DKMTQueryResourceInfo_()
        {
            auto fn = dx_func(D3DKMTQueryResourceInfo_i);
            HRESULT result = fn ? D3DKMTQueryResourceInfo_t(fn)() : E_NOTIMPL;
            return result;
        }

        // Submits the current command buffer to the Microsoft DirectX graphics kernel subsystem (Dxgkrnl.sys).
        // https://docs.microsoft.com/en-us/windows-hardware/drivers/ddi/content/d3dkmthk/nf-d3dkmthk-d3dkmtrender
        //NTSTATUS APIENTRY D3DKMTRender_(D3DKMT_RENDER* Arg1)
        HRESULT WINAPI D3DKMTRender_()
        {
            auto fn = dx_func(D3DKMTRender_i);
            HRESULT result = fn ? D3DKMTRender_t(fn)() : E_NOTIMPL;
            return result;
        }

        // Sets the priority level of a resource or list of allocations.
        // https://docs.microsoft.com/en-us/windows-hardware/drivers/ddi/content/d3dkmthk/nf-d3dkmthk-d3dkmtsetallocationpriority
        //NTSTATUS APIENTRY D3DKMTSetAllocationPriority_(const D3DKMT_SETALLOCATIONPRIORITY* Arg1)
        HRESULT WINAPI D3DKMTSetAllocationPriority_()
        {
            auto fn = dx_func(D3DKMTSetAllocationPriority_i);
            HRESULT result = fn ? D3DKMTSetAllocationPriority_t(fn)() : E_NOTIMPL;
            return result;
        }

        // Sets the scheduling priority for a device context.
        // https://docs.microsoft.com/en-us/windows-hardware/drivers/ddi/content/d3dkmthk/nf-d3dkmthk-d3dkmtsetcontextschedulingpriority
        //NTSTATUS APIENTRY D3DKMTSetContextSchedulingPriority_(const D3DKMT_SETCONTEXTSCHEDULINGPRIORITY* Arg1)
        HRESULT WINAPI D3DKMTSetContextSchedulingPriority_()
        {
            auto fn = dx_func(D3DKMTSetContextSchedulingPriority_i);
            HRESULT result = fn ? D3DKMTSetContextSchedulingPriority_t(fn)() : E_NOTIMPL;
            return result;
        }

        // Sets the allocation that is used to scan out to the display.
        // https://docs.microsoft.com/en-us/windows-hardware/drivers/ddi/content/d3dkmthk/nf-d3dkmthk-d3dkmtsetdisplaymode
        //NTSTATUS APIENTRY D3DKMTSetDisplayMode_(const D3DKMT_SETDISPLAYMODE* Arg1)
        HRESULT WINAPI D3DKMTSetDisplayMode_()
        {
            auto fn = dx_func(D3DKMTSetDisplayMode_i);
            HRESULT result = fn ? D3DKMTSetDisplayMode_t(fn)() : E_NOTIMPL;
            return result;
        }

        // Changes the private-format attribute of a video present source.
        // https://docs.microsoft.com/en-us/windows-hardware/drivers/ddi/content/d3dkmthk/nf-d3dkmthk-d3dkmtsetdisplayprivatedriverformat
        //NTSTATUS APIENTRY D3DKMTSetDisplayPrivateDriverFormat_(const D3DKMT_SETDISPLAYPRIVATEDRIVERFORMAT* Arg1)
        HRESULT WINAPI D3DKMTSetDisplayPrivateDriverFormat_()
        {
            auto fn = dx_func(D3DKMTSetDisplayPrivateDriverFormat_i);
            HRESULT result = fn ? D3DKMTSetDisplayPrivateDriverFormat_t(fn)() : E_NOTIMPL;
            return result;
        }

        // Sets the gamma ramp.
        // https://docs.microsoft.com/en-us/windows-hardware/drivers/ddi/content/d3dkmthk/nf-d3dkmthk-d3dkmtsetgammaramp
        //NTSTATUS APIENTRY D3DKMTSetGammaRamp_(const D3DKMT_SETGAMMARAMP* Arg1)
        HRESULT WINAPI D3DKMTSetGammaRamp_()
        {
            auto fn = dx_func(D3DKMTSetGammaRamp_i);
            HRESULT result = fn ? D3DKMTSetGammaRamp_t(fn)() : E_NOTIMPL;
            return result;
        }

        // Sets and releases the video present source in the path of a video present network (VidPN) topology that owns the VidPN.
        // https://docs.microsoft.com/en-us/windows-hardware/drivers/ddi/content/d3dkmthk/nf-d3dkmthk-d3dkmtsetvidpnsourceowner
        //NTSTATUS APIENTRY D3DKMTSetVidPnSourceOwner_(const D3DKMT_SETVIDPNSOURCEOWNER* Arg1)
        HRESULT WINAPI D3DKMTSetVidPnSourceOwner_()
        {
            auto fn = dx_func(D3DKMTSetVidPnSourceOwner_i);
            HRESULT result = fn ? D3DKMTSetVidPnSourceOwner_t(fn)() : E_NOTIMPL;
            return result;
        }

        // Inserts a signal for the specified synchronization objects in the specified context stream.
        // https://docs.microsoft.com/en-us/windows-hardware/drivers/ddi/content/d3dkmthk/nf-d3dkmthk-d3dkmtsignalsynchronizationobject
        //NTSTATUS APIENTRY D3DKMTSignalSynchronizationObject_(const D3DKMT_SIGNALSYNCHRONIZATIONOBJECT* Arg1)
        HRESULT WINAPI D3DKMTSignalSynchronizationObject_()
        {
            auto fn = dx_func(D3DKMTSignalSynchronizationObject_i);
            HRESULT result = fn ? D3DKMTSignalSynchronizationObject_t(fn)() : E_NOTIMPL;
            return result;
        }

        // Unlocks a list of allocations.
        // https://docs.microsoft.com/en-us/windows-hardware/drivers/ddi/content/d3dkmthk/nf-d3dkmthk-d3dkmtunlock
        //NTSTATUS APIENTRY D3DKMTUnlock_(const D3DKMT_UNLOCK* Arg1)
        HRESULT WINAPI D3DKMTUnlock_()
        {
            auto fn = dx_func(D3DKMTUnlock_i);
            HRESULT result = fn ? D3DKMTUnlock_t(fn)() : E_NOTIMPL;
            return result;
        }

        // Inserts a wait for the specified synchronization objects in the specified context stream.
        // https://docs.microsoft.com/en-us/windows-hardware/drivers/ddi/content/d3dkmthk/nf-d3dkmthk-d3dkmtwaitforsynchronizationobject
        //NTSTATUS APIENTRY D3DKMTWaitForSynchronizationObject_(const D3DKMT_WAITFORSYNCHRONIZATIONOBJECT* Arg1)
        HRESULT WINAPI D3DKMTWaitForSynchronizationObject_()
        {
            auto fn = dx_func(D3DKMTWaitForSynchronizationObject_i);
            HRESULT result = fn ? D3DKMTWaitForSynchronizationObject_t(fn)() : E_NOTIMPL;
            return result;
        }

        // Waits for the vertical blanking interval to occur and then returns.
        // https://docs.microsoft.com/en-us/windows-hardware/drivers/ddi/content/d3dkmthk/nf-d3dkmthk-d3dkmtwaitforverticalblankevent
        //NTSTATUS APIENTRY D3DKMTWaitForVerticalBlankEvent_(const D3DKMT_WAITFORVERTICALBLANKEVENT* Arg1)
        HRESULT WINAPI D3DKMTWaitForVerticalBlankEvent_()
        {
            auto fn = dx_func(D3DKMTWaitForVerticalBlankEvent_i);
            HRESULT result = fn ? D3DKMTWaitForVerticalBlankEvent_t(fn)() : E_NOTIMPL;
            return result;
        }

        //////////////////// UNDOCUMENTED FUNCTIONS ////////////////////

        void* D3DPerformance_BeginEvent_(void* unknown0, void* unknown1)
        {
            auto fn = dx_func(D3DPerformance_BeginEvent_i);
            void* result = fn ? D3DPerformance_BeginEvent_t(fn)(unknown0, unknown1) : (void*)E_NOTIMPL;
            return result;
        }

        void* D3DPerformance_EndEvent_(void** unknown0)
        {
            auto fn = dx_func(D3DPerformance_EndEvent_i);
            void* result = fn ? D3DPerformance_EndEvent_t(fn)(unknown0) : (void*)E_NOTIMPL;
            return result;
        }

        void* D3DPerformance_GetStatus_(void** unknown0)
        {
            auto fn = dx_func(D3DPerformance_GetStatus_i);
            void* result = fn ? D3DPerformance_GetStatus_t(fn)(unknown0) : (void*)E_NOTIMPL;
            return result;
        }

        UINT D3DPerformance_SetMarker_(void* unknown0, void* unknown1)
        {
            auto fn = dx_func(D3DPerformance_SetMarker_i);
            UINT result = fn ? D3DPerformance_SetMarker_t(fn)(unknown0, unknown1) : (UINT)E_NOTIMPL;
            return result;
        }

        void* WINAPI EnableFeatureLevelUpgrade_()
        {
            auto fn = dx_func(EnableFeatureLevelUpgrade_i);
            void* result = fn ? EnableFeatureLevelUpgrade_t(fn)() : (void*)E_NOTIMPL;
            return result;
        }

        ///////////////// END OF UNDOCUMENTED FUNCTIONS /////////////////

        // Creates a graphics adapter object that is referenced in subsequent calls.
        // https://docs.microsoft.com/en-us/windows-hardware/drivers/ddi/content/d3d10umddi/nc-d3d10umddi-pfnd3d10ddi_openadapter
        //HRESULT APIENTRY OpenAdapter10(D3D10DDIARG_OPENADAPTER* pOpenData)
        HRESULT WINAPI OpenAdapter10_(void* pOpenData)
        {
            HRESULT result = OpenAdapter10_t(dx_func(OpenAdapter10_i))(pOpenData);
            return result;
        }

        // Creates a graphics adapter object that is referenced in subsequent calls.
        // https://msdn.microsoft.com/en-us/library/windows/hardware/ff568603%28v=vs.85%29.aspx
        //HRESULT APIENTRY OpenAdapter10_2(_Inout_ D3D10DDIARG_OPENADAPTER* pOpenData)
        HRESULT WINAPI OpenAdapter10_2_(_Inout_ void* pOpenData)
        {
            HRESULT result = OpenAdapter10_2_t(dx_func(OpenAdapter10_2_i))(pOpenData);
            return result;
        }

    }

} // namespace d3d11