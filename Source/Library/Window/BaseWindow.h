/*+===================================================================
  File:      BASEWINDOW.H

  Summary:   BaseWindow header file contains declarations of the 
             base class of all windows used in the library.

  Classes: BaseWindow<DerivedType>

  © 2022 Kyung Hee University
===================================================================+*/
#pragma once

#include "Common.h"

namespace library
{
    /*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
      Class:    BaseWindow

      Summary:  An abstract base class from specific window

      Methods:  WindowProc
                  The window procedure of the window
                Initialize
                    Purely virtual function that initializes window
                GetWindowClassName
                    Purely virtual function that returns the name of 
                    the window class
                HandleMessage
                    Purely virtual function that that handles the 
                    messages
                GetWindow
                    Getter for the handle to the window
                BaseWindow
                    Constructor.
                ~BaseWindow
                    Destructor.
    C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/
    template <class DerivedType>
    class BaseWindow
    {
    public:
        static LRESULT CALLBACK window_proc(_In_ HWND hWnd, _In_ UINT uMsg, _In_ WPARAM wParam, _In_ LPARAM lParam);

        BaseWindow();
        BaseWindow(const BaseWindow& rhs) = delete;
        BaseWindow(BaseWindow&& rhs) = delete;
        BaseWindow& operator=(const BaseWindow& rhs) = delete;
        BaseWindow& operator=(BaseWindow&& rhs) = delete;
        virtual ~BaseWindow() = default;

        virtual HRESULT Initialize(_In_ HINSTANCE hInstance, _In_ INT nCmdShow, _In_ PCWSTR pszWindowName) = 0;
        virtual PCWSTR GetWindowClassName() const = 0;
        virtual LRESULT HandleMessage(_In_ UINT uMsg, _In_ WPARAM wParam, _In_ LPARAM lParam) = 0;

        HWND GetWindow() const;

    protected:
        HRESULT initialize(
            _In_ HINSTANCE hInstance,
            _In_ INT nCmdShow,
            _In_ PCWSTR pszWindowName,
            _In_ DWORD dwStyle,
            _In_opt_ INT x = CW_USEDEFAULT,
            _In_opt_ INT y = CW_USEDEFAULT,
            _In_opt_ INT nWidth = CW_USEDEFAULT,
            _In_opt_ INT nHeight = CW_USEDEFAULT,
            _In_opt_ HWND hWndParent = nullptr,
            _In_opt_ HMENU hMenu = nullptr
        );

        HINSTANCE m_hInstance;
        HWND m_hWnd;
        LPCWSTR m_pszWindowName;
    };

    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
        Method:   BaseWindow<DerivedType>::WindowProc

        Summary:  Defines the behavior of the window—its appearance, how
                it interacts with the user, and so forth

        Args:     HWND hWnd
                    Handle to the window
                UINT uMessage
                    Message code
                WPARAM wParam
                    Additional data the pertains to the message
                LPARAM lParam
                    Additional data the pertains to the message

        Modifies: [m_hWnd].

        Returns:  LRESULT
                    Integer value that your program returns to Windows
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    /*--------------------------------------------------------------------
      TODO: BaseWindow<DerivedType>::WindowProc definition (remove the comment)
    --------------------------------------------------------------------*/
    template <class DerivedType>
    LRESULT BaseWindow<DerivedType>::window_proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        DerivedType* pThis = NULL;

        if (uMsg == WM_NCCREATE)
        {
            CREATESTRUCT* pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);
            pThis = reinterpret_cast<DerivedType*>(pCreate->lpCreateParams);
            SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pThis));
            pThis->m_hwnd = hWnd;
        }
        else
        {
            LONG_PTR ptr = GetWindowLongPtr(hWnd, GWLP_USERDATA);
            pThis = reinterpret_cast<DerivedType*>(ptr);
        }
        if (pThis)
        {
            return pThis->HandleMessage(uMsg, wParam, lParam);
        }
        else
        {
            return DefWindowProc(hWnd, uMsg, wParam, lParam);
        }
    }


    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
        Method:   BaseWindow<DerivedType>::BaseWindow
        Summary:  Constructor
        Modifies: [m_hInstance, m_hWnd, m_pszWindowName].
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    /*--------------------------------------------------------------------
      TODO: BaseWindow<DerivedType>::BaseWindow definition (remove the comment)
    --------------------------------------------------------------------*/
    template <class DerivedType>
    BaseWindow<DerivedType>::BaseWindow()
    {
        m_hInstance = nullptr;
        m_hWnd = nullptr;
        m_pszWindowName = nullptr;
    }

    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
        Method:   BaseWindow<DerivedType>::GetWindow()

        Summary:  Returns the handle to the window

        Returns:  HWND
                    The handle to the window
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    /*--------------------------------------------------------------------
      TODO: BaseWindow<DerivedType>::GetWindow definition (remove the comment)
    --------------------------------------------------------------------*/
    template <class DerivedType>
    HWND BaseWindow<DerivedType>::GetWindow() const
    {
        return m_hWnd;
    }


    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   BaseWindow<DerivedType>::initialize

      Summary:  Registers the window class and creates a window

      Args:     HINSTANCE hInstance
                  Handle to the instance
                INT nCmdShow
                  Is a flag that says whether the main application window
                  will be minimized, maximized, or shown normally
                PCWSTR pszWindowName
                  The window name
                DWORD dwStyle
                  The style of the window being created
                INT x
                  The initial horizontal position of the window
                INT y
                  The initial vertical position of the window
                INT nWidth
                  The width, in device units, of the window
                INT nHeight
                  The height, in device units, of the window
                HWND hWndParent
                  A handle to the parent or owner window of the window
                  being created
                HMENU hMenu
                  A handle to a menu, or specifies a child-window 
                  identifier depending on the window style

                
      Modifies: [m_hInstance, m_pszWindowName, m_hWnd].

      Returns:  HRESULT
                  Status code
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    /*--------------------------------------------------------------------
      TODO: BaseWindow<DerivedType>::initialize definition (remove the comment)
    --------------------------------------------------------------------*/
    template <class DerivedType>
    HRESULT BaseWindow<DerivedType>::initialize(HINSTANCE hInstance, INT nCmdShow, PCWSTR pszWindowName, DWORD dwStyle,
        INT x, INT y, INT nWidth, INT nHeight, HWND hWndParent, HMENU hMenu)
    {
        DerivedType* pState = new (std::nothrow) DerivedType;

        if (pState == nullptr)
        {
            return 0;
        }

        // Create window
        m_hInstance = hInstance;
        AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
        m_hWnd = CreateWindowEx(0, GetWindowClassName(), pszWindowName, dwStyle, x, y, nWidth, nHeight, hWndParent, hMenu,
            hInstance, pState);

        if (!m_hWnd)
            return E_FAIL;

        ShowWindow(m_hWnd, nCmdShow);

        return S_OK;
    }

}
