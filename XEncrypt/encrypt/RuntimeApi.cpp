﻿#include "RuntimeApi.h"
#include "service/XService.h"
#include "service/XContext.h"

using namespace xencrypt;

void xencrypt_service_initialize(void* plugin)
{
    XService::Initialize(reinterpret_cast<XEncryptPlugin*>(plugin));
}

void xencrypt_service_deinitialize()
{
    XService::UnInitialize();
}

void* xencrypt_service_register_plugin(void* plugin)
{
    return XService::RegisterPlugin(reinterpret_cast<XEncryptPlugin*>(plugin));
}

void* xencrypt_create_xcontext(int type)
{
    return (void*)XService::CreateContext((XContextType)type);
}

void xencrypt_release_xcontext(void* context)
{
    XService::ReleaseContext(reinterpret_cast<XContext*>(context));
}

int xencrypt_service_decrypt(void* context, const byte* in, int64_t in_size, void** out, int64_t* out_size)
{
    XContext* x = reinterpret_cast<XContext*>(context);
    ResultCode code = XService::Decrypt(x, in, in_size);   
    int64_t dataLength = 0;
    void* pOut = nullptr;
    if (x != nullptr)
    {
        pOut = x->GetResultData();
        dataLength = x->GetResultDataLength();
    }
    if (out_size != nullptr)
    {
        *out_size = dataLength;
    }
    if (out != nullptr)
    {
        *out = pOut;
    }
    return code;
}

int xencrypt_service_encrypt(void* context, const byte* in, int64_t in_size, void** out, int64_t* out_size)
{
    XContext* x = reinterpret_cast<XContext*>(context);
    ResultCode code = XService::Encrypt(x, in, in_size);   
    int64_t dataLength = 0;
    void* pOut = nullptr;
    if (x != nullptr)
    {
        pOut = x->GetResultData();
        dataLength = x->GetResultDataLength();
    }
    if (out_size != nullptr)
    {
        *out_size = dataLength;
    }
    if (out != nullptr)
    {
        *out = pOut;
    }
    return code;
}
