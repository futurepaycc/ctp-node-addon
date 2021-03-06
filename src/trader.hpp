
#ifndef TRADE_XX_3399_
#define TRADE_XX_3399_

#include "./common.hpp"
#include "ctp6.3.15//ThostFtdcTraderApi.h"
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

namespace addon {
class TraderApi : public CThostFtdcTraderSpi,
                  public Napi::ObjectWrap<TraderApi> {
public:
  void callJS(Message *msg) {
    napi_status status = tsfn_.BlockingCall(
        msg, [](Napi::Env env, Function jsCallback, Message *msg) {
          if (msg->argc_ == 2) {
            jsCallback.Call({String::New(env, msg->type_)});
          } else if (msg->argc_ == 6) {
            Napi::Value ab;
            if (msg->data_) {
              ab = Napi::ArrayBuffer::New(env, msg->data_, msg->data_len_);
            } else {
              ab = Napi::ArrayBuffer::New(env, 0);
            }
            jsCallback.Call({String::New(env, msg->type_), ab,
                             Napi::Number::New(env, msg->error_id_),
                             Napi::ArrayBuffer::New(env, msg->error_msg_,
                                                    sizeof(msg->error_msg_)),
                             Napi::Number::New(env, msg->request_id_),
                             Napi::Boolean::New(env, msg->is_last_)});
          }
          delete msg;
        });
    if (status != napi_ok) {
      std::cout << "ERROR = " << status << std::endl;
    }
  }

  static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    static Napi::FunctionReference constructor;
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(
        env, "TraderApi",
        {
            InstanceMethod("GetApiVersion", &TraderApi::GetApiVersion),
            InstanceMethod("Release", &TraderApi::Release),
            InstanceMethod("Init", &TraderApi::Init),
            InstanceMethod("Join", &TraderApi::Join),
            InstanceMethod("GetTradingDay", &TraderApi::GetTradingDay),
            InstanceMethod("RegisterFront", &TraderApi::RegisterFront),
            InstanceMethod("RegisterNameServer",
                           &TraderApi::RegisterNameServer),
            InstanceMethod("RegisterFensUserInfo",
                           &TraderApi::RegisterFensUserInfo),
            InstanceMethod("SubscribePrivateTopic",
                           &TraderApi::SubscribePrivateTopic),
            InstanceMethod("SubscribePublicTopic",
                           &TraderApi::SubscribePublicTopic),
            InstanceMethod("ReqAuthenticate", &TraderApi::ReqAuthenticate),
            InstanceMethod("RegisterUserSystemInfo",
                           &TraderApi::RegisterUserSystemInfo),
            InstanceMethod("SubmitUserSystemInfo",
                           &TraderApi::SubmitUserSystemInfo),
            InstanceMethod("ReqUserLogin", &TraderApi::ReqUserLogin),
            InstanceMethod("ReqUserLogout", &TraderApi::ReqUserLogout),
            InstanceMethod("ReqUserPasswordUpdate",
                           &TraderApi::ReqUserPasswordUpdate),
            InstanceMethod("ReqTradingAccountPasswordUpdate",
                           &TraderApi::ReqTradingAccountPasswordUpdate),
            InstanceMethod("ReqUserAuthMethod", &TraderApi::ReqUserAuthMethod),
            InstanceMethod("ReqGenUserCaptcha", &TraderApi::ReqGenUserCaptcha),
            InstanceMethod("ReqGenUserText", &TraderApi::ReqGenUserText),
            InstanceMethod("ReqUserLoginWithCaptcha",
                           &TraderApi::ReqUserLoginWithCaptcha),
            InstanceMethod("ReqUserLoginWithText",
                           &TraderApi::ReqUserLoginWithText),
            InstanceMethod("ReqUserLoginWithOTP",
                           &TraderApi::ReqUserLoginWithOTP),
            InstanceMethod("ReqOrderInsert", &TraderApi::ReqOrderInsert),
            InstanceMethod("ReqParkedOrderInsert",
                           &TraderApi::ReqParkedOrderInsert),
            InstanceMethod("ReqParkedOrderAction",
                           &TraderApi::ReqParkedOrderAction),
            InstanceMethod("ReqOrderAction", &TraderApi::ReqOrderAction),
            InstanceMethod("ReqQueryMaxOrderVolume",
                           &TraderApi::ReqQueryMaxOrderVolume),
            InstanceMethod("ReqSettlementInfoConfirm",
                           &TraderApi::ReqSettlementInfoConfirm),
            InstanceMethod("ReqRemoveParkedOrder",
                           &TraderApi::ReqRemoveParkedOrder),
            InstanceMethod("ReqRemoveParkedOrderAction",
                           &TraderApi::ReqRemoveParkedOrderAction),
            InstanceMethod("ReqExecOrderInsert",
                           &TraderApi::ReqExecOrderInsert),
            InstanceMethod("ReqExecOrderAction",
                           &TraderApi::ReqExecOrderAction),
            InstanceMethod("ReqForQuoteInsert", &TraderApi::ReqForQuoteInsert),
            InstanceMethod("ReqQuoteInsert", &TraderApi::ReqQuoteInsert),
            InstanceMethod("ReqQuoteAction", &TraderApi::ReqQuoteAction),
            InstanceMethod("ReqBatchOrderAction",
                           &TraderApi::ReqBatchOrderAction),
            InstanceMethod("ReqOptionSelfCloseInsert",
                           &TraderApi::ReqOptionSelfCloseInsert),
            InstanceMethod("ReqOptionSelfCloseAction",
                           &TraderApi::ReqOptionSelfCloseAction),
            InstanceMethod("ReqCombActionInsert",
                           &TraderApi::ReqCombActionInsert),
            InstanceMethod("ReqQryOrder", &TraderApi::ReqQryOrder),
            InstanceMethod("ReqQryTrade", &TraderApi::ReqQryTrade),
            InstanceMethod("ReqQryInvestorPosition",
                           &TraderApi::ReqQryInvestorPosition),
            InstanceMethod("ReqQryTradingAccount",
                           &TraderApi::ReqQryTradingAccount),
            InstanceMethod("ReqQryInvestor", &TraderApi::ReqQryInvestor),
            InstanceMethod("ReqQryTradingCode", &TraderApi::ReqQryTradingCode),
            InstanceMethod("ReqQryInstrumentMarginRate",
                           &TraderApi::ReqQryInstrumentMarginRate),
            InstanceMethod("ReqQryInstrumentCommissionRate",
                           &TraderApi::ReqQryInstrumentCommissionRate),
            InstanceMethod("ReqQryExchange", &TraderApi::ReqQryExchange),
            InstanceMethod("ReqQryProduct", &TraderApi::ReqQryProduct),
            InstanceMethod("ReqQryInstrument", &TraderApi::ReqQryInstrument),
            InstanceMethod("ReqQryDepthMarketData",
                           &TraderApi::ReqQryDepthMarketData),
            InstanceMethod("ReqQrySettlementInfo",
                           &TraderApi::ReqQrySettlementInfo),
            InstanceMethod("ReqQryTransferBank",
                           &TraderApi::ReqQryTransferBank),
            InstanceMethod("ReqQryInvestorPositionDetail",
                           &TraderApi::ReqQryInvestorPositionDetail),
            InstanceMethod("ReqQryNotice", &TraderApi::ReqQryNotice),
            InstanceMethod("ReqQrySettlementInfoConfirm",
                           &TraderApi::ReqQrySettlementInfoConfirm),
            InstanceMethod("ReqQryInvestorPositionCombineDetail",
                           &TraderApi::ReqQryInvestorPositionCombineDetail),
            InstanceMethod("ReqQryCFMMCTradingAccountKey",
                           &TraderApi::ReqQryCFMMCTradingAccountKey),
            InstanceMethod("ReqQryEWarrantOffset",
                           &TraderApi::ReqQryEWarrantOffset),
            InstanceMethod("ReqQryInvestorProductGroupMargin",
                           &TraderApi::ReqQryInvestorProductGroupMargin),
            InstanceMethod("ReqQryExchangeMarginRate",
                           &TraderApi::ReqQryExchangeMarginRate),
            InstanceMethod("ReqQryExchangeMarginRateAdjust",
                           &TraderApi::ReqQryExchangeMarginRateAdjust),
            InstanceMethod("ReqQryExchangeRate",
                           &TraderApi::ReqQryExchangeRate),
            InstanceMethod("ReqQrySecAgentACIDMap",
                           &TraderApi::ReqQrySecAgentACIDMap),
            InstanceMethod("ReqQryProductExchRate",
                           &TraderApi::ReqQryProductExchRate),
            InstanceMethod("ReqQryProductGroup",
                           &TraderApi::ReqQryProductGroup),
            InstanceMethod("ReqQryMMInstrumentCommissionRate",
                           &TraderApi::ReqQryMMInstrumentCommissionRate),
            InstanceMethod("ReqQryMMOptionInstrCommRate",
                           &TraderApi::ReqQryMMOptionInstrCommRate),
            InstanceMethod("ReqQryInstrumentOrderCommRate",
                           &TraderApi::ReqQryInstrumentOrderCommRate),
            InstanceMethod("ReqQrySecAgentTradingAccount",
                           &TraderApi::ReqQrySecAgentTradingAccount),
            InstanceMethod("ReqQrySecAgentCheckMode",
                           &TraderApi::ReqQrySecAgentCheckMode),
            InstanceMethod("ReqQrySecAgentTradeInfo",
                           &TraderApi::ReqQrySecAgentTradeInfo),
            InstanceMethod("ReqQryOptionInstrTradeCost",
                           &TraderApi::ReqQryOptionInstrTradeCost),
            InstanceMethod("ReqQryOptionInstrCommRate",
                           &TraderApi::ReqQryOptionInstrCommRate),
            InstanceMethod("ReqQryExecOrder", &TraderApi::ReqQryExecOrder),
            InstanceMethod("ReqQryForQuote", &TraderApi::ReqQryForQuote),
            InstanceMethod("ReqQryQuote", &TraderApi::ReqQryQuote),
            InstanceMethod("ReqQryOptionSelfClose",
                           &TraderApi::ReqQryOptionSelfClose),
            InstanceMethod("ReqQryInvestUnit", &TraderApi::ReqQryInvestUnit),
            InstanceMethod("ReqQryCombInstrumentGuard",
                           &TraderApi::ReqQryCombInstrumentGuard),
            InstanceMethod("ReqQryCombAction", &TraderApi::ReqQryCombAction),
            InstanceMethod("ReqQryTransferSerial",
                           &TraderApi::ReqQryTransferSerial),
            InstanceMethod("ReqQryAccountregister",
                           &TraderApi::ReqQryAccountregister),
            InstanceMethod("ReqQryContractBank",
                           &TraderApi::ReqQryContractBank),
            InstanceMethod("ReqQryParkedOrder", &TraderApi::ReqQryParkedOrder),
            InstanceMethod("ReqQryParkedOrderAction",
                           &TraderApi::ReqQryParkedOrderAction),
            InstanceMethod("ReqQryTradingNotice",
                           &TraderApi::ReqQryTradingNotice),
            InstanceMethod("ReqQryBrokerTradingParams",
                           &TraderApi::ReqQryBrokerTradingParams),
            InstanceMethod("ReqQryBrokerTradingAlgos",
                           &TraderApi::ReqQryBrokerTradingAlgos),
            InstanceMethod("ReqQueryCFMMCTradingAccountToken",
                           &TraderApi::ReqQueryCFMMCTradingAccountToken),
            InstanceMethod("ReqFromBankToFutureByFuture",
                           &TraderApi::ReqFromBankToFutureByFuture),
            InstanceMethod("ReqFromFutureToBankByFuture",
                           &TraderApi::ReqFromFutureToBankByFuture),
            InstanceMethod("ReqQueryBankAccountMoneyByFuture",
                           &TraderApi::ReqQueryBankAccountMoneyByFuture),
        });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    exports.Set("TraderApi", func);
    return exports;
  }

  TraderApi(const Napi::CallbackInfo &info)
      : Napi::ObjectWrap<TraderApi>(info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    if (info.Length() <= 0 || !info[0].IsFunction()) {
      Napi::TypeError::New(env, "Function expected")
          .ThrowAsJavaScriptException();
      return;
    }

    api_ = CThostFtdcTraderApi::CreateFtdcTraderApi();
    api_->RegisterSpi(this);
    tsfn_ = ThreadSafeFunction::New(
        env,
        info[0].As<Function>(), // JavaScript function called asynchronously
        "Resource Name",        // Name
        0,                      // Unlimited queue
        1,                      // Only one thread will use this initially
        [](Napi::Env) {         // Finalizer used to clean threads up
          // nativeThread.join();
        });
  }

private:
  Napi::ThreadSafeFunction tsfn_;
  CThostFtdcTraderApi *api_;

  /// -- 以下为goshare/cmd/util/ctp_dump导出的代码
  Napi::Value GetApiVersion(const CallbackInfo &info) {
    return Napi::String::New(info.Env(), api_->GetApiVersion());
  }

  void Release(const CallbackInfo &info) { api_->Release(); }

  void Init(const CallbackInfo &info) { api_->Init(); }

  void Join(const CallbackInfo &info) { api_->Join(); }

  Napi::Value GetTradingDay(const CallbackInfo &info) {
    return Napi::String::New(info.Env(), api_->GetTradingDay());
  }

  void RegisterFront(const CallbackInfo &info) {
    std::string str = info[0].As<Napi::String>();
    api_->RegisterFront((char *)str.data());
  }

  void RegisterNameServer(const CallbackInfo &info) {
    std::string str = info[0].As<Napi::String>();
    api_->RegisterNameServer((char *)str.data());
  }

  void RegisterFensUserInfo(const CallbackInfo &info) {
    auto ab = info[0].As<Napi::TypedArray>().ArrayBuffer();
    CThostFtdcFensUserInfoField *req = (CThostFtdcFensUserInfoField *)ab.Data();
    api_->RegisterFensUserInfo(req);
  }

  void SubscribePrivateTopic(const CallbackInfo &info) {
    int32_t nResumeType = info[0].As<Napi::Number>().Int32Value();
    api_->SubscribePrivateTopic((THOST_TE_RESUME_TYPE)nResumeType);
  }

  void SubscribePublicTopic(const CallbackInfo &info) {
    int32_t nResumeType = info[0].As<Napi::Number>().Int32Value();
    api_->SubscribePublicTopic((THOST_TE_RESUME_TYPE)nResumeType);
  }

  void ReqAuthenticate(const CallbackInfo &info) {
    auto ab = info[0].As<Napi::TypedArray>().ArrayBuffer();
    int32_t nRequestID = info[1].As<Napi::Number>().Int32Value();
    CThostFtdcReqAuthenticateField *req =
        (CThostFtdcReqAuthenticateField *)ab.Data();
    api_->ReqAuthenticate(req, nRequestID);
  }

  void RegisterUserSystemInfo(const CallbackInfo &info) {
    auto ab = info[0].As<Napi::TypedArray>().ArrayBuffer();
    CThostFtdcUserSystemInfoField *req =
        (CThostFtdcUserSystemInfoField *)ab.Data();
    api_->RegisterUserSystemInfo(req);
  }

  void SubmitUserSystemInfo(const CallbackInfo &info) {
    auto ab = info[0].As<Napi::TypedArray>().ArrayBuffer();
    CThostFtdcUserSystemInfoField *req =
        (CThostFtdcUserSystemInfoField *)ab.Data();
    api_->SubmitUserSystemInfo(req);
  }

  void ReqUserLogin(const CallbackInfo &info) {
    auto ab = info[0].As<Napi::TypedArray>().ArrayBuffer();
    int32_t nRequestID = info[1].As<Napi::Number>().Int32Value();
    CThostFtdcReqUserLoginField *req = (CThostFtdcReqUserLoginField *)ab.Data();
    api_->ReqUserLogin(req, nRequestID);
  }

  void ReqUserLogout(const CallbackInfo &info) {
    auto ab = info[0].As<Napi::TypedArray>().ArrayBuffer();
    int32_t nRequestID = info[1].As<Napi::Number>().Int32Value();
    CThostFtdcUserLogoutField *req = (CThostFtdcUserLogoutField *)ab.Data();
    api_->ReqUserLogout(req, nRequestID);
  }

  void ReqUserPasswordUpdate(const CallbackInfo &info) {
    auto ab = info[0].As<Napi::TypedArray>().ArrayBuffer();
    int32_t nRequestID = info[1].As<Napi::Number>().Int32Value();
    CThostFtdcUserPasswordUpdateField *req =
        (CThostFtdcUserPasswordUpdateField *)ab.Data();
    api_->ReqUserPasswordUpdate(req, nRequestID);
  }

  void ReqTradingAccountPasswordUpdate(const CallbackInfo &info) {
    auto ab = info[0].As<Napi::TypedArray>().ArrayBuffer();
    int32_t nRequestID = info[1].As<Napi::Number>().Int32Value();
    CThostFtdcTradingAccountPasswordUpdateField *req =
        (CThostFtdcTradingAccountPasswordUpdateField *)ab.Data();
    api_->ReqTradingAccountPasswordUpdate(req, nRequestID);
  }

  void ReqUserAuthMethod(const CallbackInfo &info) {
    auto ab = info[0].As<Napi::TypedArray>().ArrayBuffer();
    int32_t nRequestID = info[1].As<Napi::Number>().Int32Value();
    CThostFtdcReqUserAuthMethodField *req =
        (CThostFtdcReqUserAuthMethodField *)ab.Data();
    api_->ReqUserAuthMethod(req, nRequestID);
  }

  void ReqGenUserCaptcha(const CallbackInfo &info) {
    auto ab = info[0].As<Napi::TypedArray>().ArrayBuffer();
    int32_t nRequestID = info[1].As<Napi::Number>().Int32Value();
    CThostFtdcReqGenUserCaptchaField *req =
        (CThostFtdcReqGenUserCaptchaField *)ab.Data();
    api_->ReqGenUserCaptcha(req, nRequestID);
  }

  void ReqGenUserText(const CallbackInfo &info) {
    auto ab = info[0].As<Napi::TypedArray>().ArrayBuffer();
    int32_t nRequestID = info[1].As<Napi::Number>().Int32Value();
    CThostFtdcReqGenUserTextField *req =
        (CThostFtdcReqGenUserTextField *)ab.Data();
    api_->ReqGenUserText(req, nRequestID);
  }

  void ReqUserLoginWithCaptcha(const CallbackInfo &info) {
    auto ab = info[0].As<Napi::TypedArray>().ArrayBuffer();
    int32_t nRequestID = info[1].As<Napi::Number>().Int32Value();
    CThostFtdcReqUserLoginWithCaptchaField *req =
        (CThostFtdcReqUserLoginWithCaptchaField *)ab.Data();
    api_->ReqUserLoginWithCaptcha(req, nRequestID);
  }

  void ReqUserLoginWithText(const CallbackInfo &info) {
    auto ab = info[0].As<Napi::TypedArray>().ArrayBuffer();
    int32_t nRequestID = info[1].As<Napi::Number>().Int32Value();
    CThostFtdcReqUserLoginWithTextField *req =
        (CThostFtdcReqUserLoginWithTextField *)ab.Data();
    api_->ReqUserLoginWithText(req, nRequestID);
  }

  void ReqUserLoginWithOTP(const CallbackInfo &info) {
    auto ab = info[0].As<Napi::TypedArray>().ArrayBuffer();
    int32_t nRequestID = info[1].As<Napi::Number>().Int32Value();
    CThostFtdcReqUserLoginWithOTPField *req =
        (CThostFtdcReqUserLoginWithOTPField *)ab.Data();
    api_->ReqUserLoginWithOTP(req, nRequestID);
  }

  void ReqOrderInsert(const CallbackInfo &info) {
    auto ab = info[0].As<Napi::TypedArray>().ArrayBuffer();
    int32_t nRequestID = info[1].As<Napi::Number>().Int32Value();
    CThostFtdcInputOrderField *req = (CThostFtdcInputOrderField *)ab.Data();
    api_->ReqOrderInsert(req, nRequestID);
  }

  void ReqParkedOrderInsert(const CallbackInfo &info) {
    auto ab = info[0].As<Napi::TypedArray>().ArrayBuffer();
    int32_t nRequestID = info[1].As<Napi::Number>().Int32Value();
    CThostFtdcParkedOrderField *req = (CThostFtdcParkedOrderField *)ab.Data();
    api_->ReqParkedOrderInsert(req, nRequestID);
  }

  void ReqParkedOrderAction(const CallbackInfo &info) {
    auto ab = info[0].As<Napi::TypedArray>().ArrayBuffer();
    int32_t nRequestID = info[1].As<Napi::Number>().Int32Value();
    CThostFtdcParkedOrderActionField *req =
        (CThostFtdcParkedOrderActionField *)ab.Data();
    api_->ReqParkedOrderAction(req, nRequestID);
  }

  void ReqOrderAction(const CallbackInfo &info) {
    auto ab = info[0].As<Napi::TypedArray>().ArrayBuffer();
    int32_t nRequestID = info[1].As<Napi::Number>().Int32Value();
    CThostFtdcInputOrderActionField *req =
        (CThostFtdcInputOrderActionField *)ab.Data();
    api_->ReqOrderAction(req, nRequestID);
  }

  void ReqQueryMaxOrderVolume(const CallbackInfo &info) {
    auto ab = info[0].As<Napi::TypedArray>().ArrayBuffer();
    int32_t nRequestID = info[1].As<Napi::Number>().Int32Value();
    CThostFtdcQueryMaxOrderVolumeField *req =
        (CThostFtdcQueryMaxOrderVolumeField *)ab.Data();
    api_->ReqQueryMaxOrderVolume(req, nRequestID);
  }

  void ReqSettlementInfoConfirm(const CallbackInfo &info) {
    auto ab = info[0].As<Napi::TypedArray>().ArrayBuffer();
    int32_t nRequestID = info[1].As<Napi::Number>().Int32Value();
    CThostFtdcSettlementInfoConfirmField *req =
        (CThostFtdcSettlementInfoConfirmField *)ab.Data();
    api_->ReqSettlementInfoConfirm(req, nRequestID);
  }

  void ReqRemoveParkedOrder(const CallbackInfo &info) {
    auto ab = info[0].As<Napi::TypedArray>().ArrayBuffer();
    int32_t nRequestID = info[1].As<Napi::Number>().Int32Value();
    CThostFtdcRemoveParkedOrderField *req =
        (CThostFtdcRemoveParkedOrderField *)ab.Data();
    api_->ReqRemoveParkedOrder(req, nRequestID);
  }

  void ReqRemoveParkedOrderAction(const CallbackInfo &info) {
    auto ab = info[0].As<Napi::TypedArray>().ArrayBuffer();
    int32_t nRequestID = info[1].As<Napi::Number>().Int32Value();
    CThostFtdcRemoveParkedOrderActionField *req =
        (CThostFtdcRemoveParkedOrderActionField *)ab.Data();
    api_->ReqRemoveParkedOrderAction(req, nRequestID);
  }

  void ReqExecOrderInsert(const CallbackInfo &info) {
    auto ab = info[0].As<Napi::TypedArray>().ArrayBuffer();
    int32_t nRequestID = info[1].As<Napi::Number>().Int32Value();
    CThostFtdcInputExecOrderField *req =
        (CThostFtdcInputExecOrderField *)ab.Data();
    api_->ReqExecOrderInsert(req, nRequestID);
  }

  void ReqExecOrderAction(const CallbackInfo &info) {
    auto ab = info[0].As<Napi::TypedArray>().ArrayBuffer();
    int32_t nRequestID = info[1].As<Napi::Number>().Int32Value();
    CThostFtdcInputExecOrderActionField *req =
        (CThostFtdcInputExecOrderActionField *)ab.Data();
    api_->ReqExecOrderAction(req, nRequestID);
  }

  void ReqForQuoteInsert(const CallbackInfo &info) {
    auto ab = info[0].As<Napi::TypedArray>().ArrayBuffer();
    int32_t nRequestID = info[1].As<Napi::Number>().Int32Value();
    CThostFtdcInputForQuoteField *req =
        (CThostFtdcInputForQuoteField *)ab.Data();
    api_->ReqForQuoteInsert(req, nRequestID);
  }

  void ReqQuoteInsert(const CallbackInfo &info) {
    auto ab = info[0].As<Napi::TypedArray>().ArrayBuffer();
    int32_t nRequestID = info[1].As<Napi::Number>().Int32Value();
    CThostFtdcInputQuoteField *req = (CThostFtdcInputQuoteField *)ab.Data();
    api_->ReqQuoteInsert(req, nRequestID);
  }

  void ReqQuoteAction(const CallbackInfo &info) {
    auto ab = info[0].As<Napi::TypedArray>().ArrayBuffer();
    int32_t nRequestID = info[1].As<Napi::Number>().Int32Value();
    CThostFtdcInputQuoteActionField *req =
        (CThostFtdcInputQuoteActionField *)ab.Data();
    api_->ReqQuoteAction(req, nRequestID);
  }

  void ReqBatchOrderAction(const CallbackInfo &info) {
    auto ab = info[0].As<Napi::TypedArray>().ArrayBuffer();
    int32_t nRequestID = info[1].As<Napi::Number>().Int32Value();
    CThostFtdcInputBatchOrderActionField *req =
        (CThostFtdcInputBatchOrderActionField *)ab.Data();
    api_->ReqBatchOrderAction(req, nRequestID);
  }

  void ReqOptionSelfCloseInsert(const CallbackInfo &info) {
    auto ab = info[0].As<Napi::TypedArray>().ArrayBuffer();
    int32_t nRequestID = info[1].As<Napi::Number>().Int32Value();
    CThostFtdcInputOptionSelfCloseField *req =
        (CThostFtdcInputOptionSelfCloseField *)ab.Data();
    api_->ReqOptionSelfCloseInsert(req, nRequestID);
  }

  void ReqOptionSelfCloseAction(const CallbackInfo &info) {
    auto ab = info[0].As<Napi::TypedArray>().ArrayBuffer();
    int32_t nRequestID = info[1].As<Napi::Number>().Int32Value();
    CThostFtdcInputOptionSelfCloseActionField *req =
        (CThostFtdcInputOptionSelfCloseActionField *)ab.Data();
    api_->ReqOptionSelfCloseAction(req, nRequestID);
  }

  void ReqCombActionInsert(const CallbackInfo &info) {
    auto ab = info[0].As<Napi::TypedArray>().ArrayBuffer();
    int32_t nRequestID = info[1].As<Napi::Number>().Int32Value();
    CThostFtdcInputCombActionField *req =
        (CThostFtdcInputCombActionField *)ab.Data();
    api_->ReqCombActionInsert(req, nRequestID);
  }

  void ReqQryOrder(const CallbackInfo &info) {
    auto ab = info[0].As<Napi::TypedArray>().ArrayBuffer();
    int32_t nRequestID = info[1].As<Napi::Number>().Int32Value();
    CThostFtdcQryOrderField *req = (CThostFtdcQryOrderField *)ab.Data();
    api_->ReqQryOrder(req, nRequestID);
  }

  void ReqQryTrade(const CallbackInfo &info) {
    auto ab = info[0].As<Napi::TypedArray>().ArrayBuffer();
    int32_t nRequestID = info[1].As<Napi::Number>().Int32Value();
    CThostFtdcQryTradeField *req = (CThostFtdcQryTradeField *)ab.Data();
    api_->ReqQryTrade(req, nRequestID);
  }

  void ReqQryInvestorPosition(const CallbackInfo &info) {
    auto ab = info[0].As<Napi::TypedArray>().ArrayBuffer();
    int32_t nRequestID = info[1].As<Napi::Number>().Int32Value();
    CThostFtdcQryInvestorPositionField *req =
        (CThostFtdcQryInvestorPositionField *)ab.Data();
    api_->ReqQryInvestorPosition(req, nRequestID);
  }

  void ReqQryTradingAccount(const CallbackInfo &info) {
    auto ab = info[0].As<Napi::TypedArray>().ArrayBuffer();
    int32_t nRequestID = info[1].As<Napi::Number>().Int32Value();
    CThostFtdcQryTradingAccountField *req =
        (CThostFtdcQryTradingAccountField *)ab.Data();
    api_->ReqQryTradingAccount(req, nRequestID);
  }

  void ReqQryInvestor(const CallbackInfo &info) {
    auto ab = info[0].As<Napi::TypedArray>().ArrayBuffer();
    int32_t nRequestID = info[1].As<Napi::Number>().Int32Value();
    CThostFtdcQryInvestorField *req = (CThostFtdcQryInvestorField *)ab.Data();
    api_->ReqQryInvestor(req, nRequestID);
  }

  void ReqQryTradingCode(const CallbackInfo &info) {
    auto ab = info[0].As<Napi::TypedArray>().ArrayBuffer();
    int32_t nRequestID = info[1].As<Napi::Number>().Int32Value();
    CThostFtdcQryTradingCodeField *req =
        (CThostFtdcQryTradingCodeField *)ab.Data();
    api_->ReqQryTradingCode(req, nRequestID);
  }

  void ReqQryInstrumentMarginRate(const CallbackInfo &info) {
    auto ab = info[0].As<Napi::TypedArray>().ArrayBuffer();
    int32_t nRequestID = info[1].As<Napi::Number>().Int32Value();
    CThostFtdcQryInstrumentMarginRateField *req =
        (CThostFtdcQryInstrumentMarginRateField *)ab.Data();
    api_->ReqQryInstrumentMarginRate(req, nRequestID);
  }

  void ReqQryInstrumentCommissionRate(const CallbackInfo &info) {
    auto ab = info[0].As<Napi::TypedArray>().ArrayBuffer();
    int32_t nRequestID = info[1].As<Napi::Number>().Int32Value();
    CThostFtdcQryInstrumentCommissionRateField *req =
        (CThostFtdcQryInstrumentCommissionRateField *)ab.Data();
    api_->ReqQryInstrumentCommissionRate(req, nRequestID);
  }

  void ReqQryExchange(const CallbackInfo &info) {
    auto ab = info[0].As<Napi::TypedArray>().ArrayBuffer();
    int32_t nRequestID = info[1].As<Napi::Number>().Int32Value();
    CThostFtdcQryExchangeField *req = (CThostFtdcQryExchangeField *)ab.Data();
    api_->ReqQryExchange(req, nRequestID);
  }

  void ReqQryProduct(const CallbackInfo &info) {
    auto ab = info[0].As<Napi::TypedArray>().ArrayBuffer();
    int32_t nRequestID = info[1].As<Napi::Number>().Int32Value();
    CThostFtdcQryProductField *req = (CThostFtdcQryProductField *)ab.Data();
    api_->ReqQryProduct(req, nRequestID);
  }

  void ReqQryInstrument(const CallbackInfo &info) {
    auto ab = info[0].As<Napi::TypedArray>().ArrayBuffer();
    int32_t nRequestID = info[1].As<Napi::Number>().Int32Value();
    CThostFtdcQryInstrumentField *req =
        (CThostFtdcQryInstrumentField *)ab.Data();
    api_->ReqQryInstrument(req, nRequestID);
  }

  void ReqQryDepthMarketData(const CallbackInfo &info) {
    auto ab = info[0].As<Napi::TypedArray>().ArrayBuffer();
    int32_t nRequestID = info[1].As<Napi::Number>().Int32Value();
    CThostFtdcQryDepthMarketDataField *req =
        (CThostFtdcQryDepthMarketDataField *)ab.Data();
    api_->ReqQryDepthMarketData(req, nRequestID);
  }

  void ReqQrySettlementInfo(const CallbackInfo &info) {
    auto ab = info[0].As<Napi::TypedArray>().ArrayBuffer();
    int32_t nRequestID = info[1].As<Napi::Number>().Int32Value();
    CThostFtdcQrySettlementInfoField *req =
        (CThostFtdcQrySettlementInfoField *)ab.Data();
    api_->ReqQrySettlementInfo(req, nRequestID);
  }

  void ReqQryTransferBank(const CallbackInfo &info) {
    auto ab = info[0].As<Napi::TypedArray>().ArrayBuffer();
    int32_t nRequestID = info[1].As<Napi::Number>().Int32Value();
    CThostFtdcQryTransferBankField *req =
        (CThostFtdcQryTransferBankField *)ab.Data();
    api_->ReqQryTransferBank(req, nRequestID);
  }

  void ReqQryInvestorPositionDetail(const CallbackInfo &info) {
    auto ab = info[0].As<Napi::TypedArray>().ArrayBuffer();
    int32_t nRequestID = info[1].As<Napi::Number>().Int32Value();
    CThostFtdcQryInvestorPositionDetailField *req =
        (CThostFtdcQryInvestorPositionDetailField *)ab.Data();
    api_->ReqQryInvestorPositionDetail(req, nRequestID);
  }

  void ReqQryNotice(const CallbackInfo &info) {
    auto ab = info[0].As<Napi::TypedArray>().ArrayBuffer();
    int32_t nRequestID = info[1].As<Napi::Number>().Int32Value();
    CThostFtdcQryNoticeField *req = (CThostFtdcQryNoticeField *)ab.Data();
    api_->ReqQryNotice(req, nRequestID);
  }

  void ReqQrySettlementInfoConfirm(const CallbackInfo &info) {
    auto ab = info[0].As<Napi::TypedArray>().ArrayBuffer();
    int32_t nRequestID = info[1].As<Napi::Number>().Int32Value();
    CThostFtdcQrySettlementInfoConfirmField *req =
        (CThostFtdcQrySettlementInfoConfirmField *)ab.Data();
    api_->ReqQrySettlementInfoConfirm(req, nRequestID);
  }

  void ReqQryInvestorPositionCombineDetail(const CallbackInfo &info) {
    auto ab = info[0].As<Napi::TypedArray>().ArrayBuffer();
    int32_t nRequestID = info[1].As<Napi::Number>().Int32Value();
    CThostFtdcQryInvestorPositionCombineDetailField *req =
        (CThostFtdcQryInvestorPositionCombineDetailField *)ab.Data();
    api_->ReqQryInvestorPositionCombineDetail(req, nRequestID);
  }

  void ReqQryCFMMCTradingAccountKey(const CallbackInfo &info) {
    auto ab = info[0].As<Napi::TypedArray>().ArrayBuffer();
    int32_t nRequestID = info[1].As<Napi::Number>().Int32Value();
    CThostFtdcQryCFMMCTradingAccountKeyField *req =
        (CThostFtdcQryCFMMCTradingAccountKeyField *)ab.Data();
    api_->ReqQryCFMMCTradingAccountKey(req, nRequestID);
  }

  void ReqQryEWarrantOffset(const CallbackInfo &info) {
    auto ab = info[0].As<Napi::TypedArray>().ArrayBuffer();
    int32_t nRequestID = info[1].As<Napi::Number>().Int32Value();
    CThostFtdcQryEWarrantOffsetField *req =
        (CThostFtdcQryEWarrantOffsetField *)ab.Data();
    api_->ReqQryEWarrantOffset(req, nRequestID);
  }

  void ReqQryInvestorProductGroupMargin(const CallbackInfo &info) {
    auto ab = info[0].As<Napi::TypedArray>().ArrayBuffer();
    int32_t nRequestID = info[1].As<Napi::Number>().Int32Value();
    CThostFtdcQryInvestorProductGroupMarginField *req =
        (CThostFtdcQryInvestorProductGroupMarginField *)ab.Data();
    api_->ReqQryInvestorProductGroupMargin(req, nRequestID);
  }

  void ReqQryExchangeMarginRate(const CallbackInfo &info) {
    auto ab = info[0].As<Napi::TypedArray>().ArrayBuffer();
    int32_t nRequestID = info[1].As<Napi::Number>().Int32Value();
    CThostFtdcQryExchangeMarginRateField *req =
        (CThostFtdcQryExchangeMarginRateField *)ab.Data();
    api_->ReqQryExchangeMarginRate(req, nRequestID);
  }

  void ReqQryExchangeMarginRateAdjust(const CallbackInfo &info) {
    auto ab = info[0].As<Napi::TypedArray>().ArrayBuffer();
    int32_t nRequestID = info[1].As<Napi::Number>().Int32Value();
    CThostFtdcQryExchangeMarginRateAdjustField *req =
        (CThostFtdcQryExchangeMarginRateAdjustField *)ab.Data();
    api_->ReqQryExchangeMarginRateAdjust(req, nRequestID);
  }

  void ReqQryExchangeRate(const CallbackInfo &info) {
    auto ab = info[0].As<Napi::TypedArray>().ArrayBuffer();
    int32_t nRequestID = info[1].As<Napi::Number>().Int32Value();
    CThostFtdcQryExchangeRateField *req =
        (CThostFtdcQryExchangeRateField *)ab.Data();
    api_->ReqQryExchangeRate(req, nRequestID);
  }

  void ReqQrySecAgentACIDMap(const CallbackInfo &info) {
    auto ab = info[0].As<Napi::TypedArray>().ArrayBuffer();
    int32_t nRequestID = info[1].As<Napi::Number>().Int32Value();
    CThostFtdcQrySecAgentACIDMapField *req =
        (CThostFtdcQrySecAgentACIDMapField *)ab.Data();
    api_->ReqQrySecAgentACIDMap(req, nRequestID);
  }

  void ReqQryProductExchRate(const CallbackInfo &info) {
    auto ab = info[0].As<Napi::TypedArray>().ArrayBuffer();
    int32_t nRequestID = info[1].As<Napi::Number>().Int32Value();
    CThostFtdcQryProductExchRateField *req =
        (CThostFtdcQryProductExchRateField *)ab.Data();
    api_->ReqQryProductExchRate(req, nRequestID);
  }

  void ReqQryProductGroup(const CallbackInfo &info) {
    auto ab = info[0].As<Napi::TypedArray>().ArrayBuffer();
    int32_t nRequestID = info[1].As<Napi::Number>().Int32Value();
    CThostFtdcQryProductGroupField *req =
        (CThostFtdcQryProductGroupField *)ab.Data();
    api_->ReqQryProductGroup(req, nRequestID);
  }

  void ReqQryMMInstrumentCommissionRate(const CallbackInfo &info) {
    auto ab = info[0].As<Napi::TypedArray>().ArrayBuffer();
    int32_t nRequestID = info[1].As<Napi::Number>().Int32Value();
    CThostFtdcQryMMInstrumentCommissionRateField *req =
        (CThostFtdcQryMMInstrumentCommissionRateField *)ab.Data();
    api_->ReqQryMMInstrumentCommissionRate(req, nRequestID);
  }

  void ReqQryMMOptionInstrCommRate(const CallbackInfo &info) {
    auto ab = info[0].As<Napi::TypedArray>().ArrayBuffer();
    int32_t nRequestID = info[1].As<Napi::Number>().Int32Value();
    CThostFtdcQryMMOptionInstrCommRateField *req =
        (CThostFtdcQryMMOptionInstrCommRateField *)ab.Data();
    api_->ReqQryMMOptionInstrCommRate(req, nRequestID);
  }

  void ReqQryInstrumentOrderCommRate(const CallbackInfo &info) {
    auto ab = info[0].As<Napi::TypedArray>().ArrayBuffer();
    int32_t nRequestID = info[1].As<Napi::Number>().Int32Value();
    CThostFtdcQryInstrumentOrderCommRateField *req =
        (CThostFtdcQryInstrumentOrderCommRateField *)ab.Data();
    api_->ReqQryInstrumentOrderCommRate(req, nRequestID);
  }

  void ReqQrySecAgentTradingAccount(const CallbackInfo &info) {
    auto ab = info[0].As<Napi::TypedArray>().ArrayBuffer();
    int32_t nRequestID = info[1].As<Napi::Number>().Int32Value();
    CThostFtdcQryTradingAccountField *req =
        (CThostFtdcQryTradingAccountField *)ab.Data();
    api_->ReqQrySecAgentTradingAccount(req, nRequestID);
  }

  void ReqQrySecAgentCheckMode(const CallbackInfo &info) {
    auto ab = info[0].As<Napi::TypedArray>().ArrayBuffer();
    int32_t nRequestID = info[1].As<Napi::Number>().Int32Value();
    CThostFtdcQrySecAgentCheckModeField *req =
        (CThostFtdcQrySecAgentCheckModeField *)ab.Data();
    api_->ReqQrySecAgentCheckMode(req, nRequestID);
  }

  void ReqQrySecAgentTradeInfo(const CallbackInfo &info) {
    auto ab = info[0].As<Napi::TypedArray>().ArrayBuffer();
    int32_t nRequestID = info[1].As<Napi::Number>().Int32Value();
    CThostFtdcQrySecAgentTradeInfoField *req =
        (CThostFtdcQrySecAgentTradeInfoField *)ab.Data();
    api_->ReqQrySecAgentTradeInfo(req, nRequestID);
  }

  void ReqQryOptionInstrTradeCost(const CallbackInfo &info) {
    auto ab = info[0].As<Napi::TypedArray>().ArrayBuffer();
    int32_t nRequestID = info[1].As<Napi::Number>().Int32Value();
    CThostFtdcQryOptionInstrTradeCostField *req =
        (CThostFtdcQryOptionInstrTradeCostField *)ab.Data();
    api_->ReqQryOptionInstrTradeCost(req, nRequestID);
  }

  void ReqQryOptionInstrCommRate(const CallbackInfo &info) {
    auto ab = info[0].As<Napi::TypedArray>().ArrayBuffer();
    int32_t nRequestID = info[1].As<Napi::Number>().Int32Value();
    CThostFtdcQryOptionInstrCommRateField *req =
        (CThostFtdcQryOptionInstrCommRateField *)ab.Data();
    api_->ReqQryOptionInstrCommRate(req, nRequestID);
  }

  void ReqQryExecOrder(const CallbackInfo &info) {
    auto ab = info[0].As<Napi::TypedArray>().ArrayBuffer();
    int32_t nRequestID = info[1].As<Napi::Number>().Int32Value();
    CThostFtdcQryExecOrderField *req = (CThostFtdcQryExecOrderField *)ab.Data();
    api_->ReqQryExecOrder(req, nRequestID);
  }

  void ReqQryForQuote(const CallbackInfo &info) {
    auto ab = info[0].As<Napi::TypedArray>().ArrayBuffer();
    int32_t nRequestID = info[1].As<Napi::Number>().Int32Value();
    CThostFtdcQryForQuoteField *req = (CThostFtdcQryForQuoteField *)ab.Data();
    api_->ReqQryForQuote(req, nRequestID);
  }

  void ReqQryQuote(const CallbackInfo &info) {
    auto ab = info[0].As<Napi::TypedArray>().ArrayBuffer();
    int32_t nRequestID = info[1].As<Napi::Number>().Int32Value();
    CThostFtdcQryQuoteField *req = (CThostFtdcQryQuoteField *)ab.Data();
    api_->ReqQryQuote(req, nRequestID);
  }

  void ReqQryOptionSelfClose(const CallbackInfo &info) {
    auto ab = info[0].As<Napi::TypedArray>().ArrayBuffer();
    int32_t nRequestID = info[1].As<Napi::Number>().Int32Value();
    CThostFtdcQryOptionSelfCloseField *req =
        (CThostFtdcQryOptionSelfCloseField *)ab.Data();
    api_->ReqQryOptionSelfClose(req, nRequestID);
  }

  void ReqQryInvestUnit(const CallbackInfo &info) {
    auto ab = info[0].As<Napi::TypedArray>().ArrayBuffer();
    int32_t nRequestID = info[1].As<Napi::Number>().Int32Value();
    CThostFtdcQryInvestUnitField *req =
        (CThostFtdcQryInvestUnitField *)ab.Data();
    api_->ReqQryInvestUnit(req, nRequestID);
  }

  void ReqQryCombInstrumentGuard(const CallbackInfo &info) {
    auto ab = info[0].As<Napi::TypedArray>().ArrayBuffer();
    int32_t nRequestID = info[1].As<Napi::Number>().Int32Value();
    CThostFtdcQryCombInstrumentGuardField *req =
        (CThostFtdcQryCombInstrumentGuardField *)ab.Data();
    api_->ReqQryCombInstrumentGuard(req, nRequestID);
  }

  void ReqQryCombAction(const CallbackInfo &info) {
    auto ab = info[0].As<Napi::TypedArray>().ArrayBuffer();
    int32_t nRequestID = info[1].As<Napi::Number>().Int32Value();
    CThostFtdcQryCombActionField *req =
        (CThostFtdcQryCombActionField *)ab.Data();
    api_->ReqQryCombAction(req, nRequestID);
  }

  void ReqQryTransferSerial(const CallbackInfo &info) {
    auto ab = info[0].As<Napi::TypedArray>().ArrayBuffer();
    int32_t nRequestID = info[1].As<Napi::Number>().Int32Value();
    CThostFtdcQryTransferSerialField *req =
        (CThostFtdcQryTransferSerialField *)ab.Data();
    api_->ReqQryTransferSerial(req, nRequestID);
  }

  void ReqQryAccountregister(const CallbackInfo &info) {
    auto ab = info[0].As<Napi::TypedArray>().ArrayBuffer();
    int32_t nRequestID = info[1].As<Napi::Number>().Int32Value();
    CThostFtdcQryAccountregisterField *req =
        (CThostFtdcQryAccountregisterField *)ab.Data();
    api_->ReqQryAccountregister(req, nRequestID);
  }

  void ReqQryContractBank(const CallbackInfo &info) {
    auto ab = info[0].As<Napi::TypedArray>().ArrayBuffer();
    int32_t nRequestID = info[1].As<Napi::Number>().Int32Value();
    CThostFtdcQryContractBankField *req =
        (CThostFtdcQryContractBankField *)ab.Data();
    api_->ReqQryContractBank(req, nRequestID);
  }

  void ReqQryParkedOrder(const CallbackInfo &info) {
    auto ab = info[0].As<Napi::TypedArray>().ArrayBuffer();
    int32_t nRequestID = info[1].As<Napi::Number>().Int32Value();
    CThostFtdcQryParkedOrderField *req =
        (CThostFtdcQryParkedOrderField *)ab.Data();
    api_->ReqQryParkedOrder(req, nRequestID);
  }

  void ReqQryParkedOrderAction(const CallbackInfo &info) {
    auto ab = info[0].As<Napi::TypedArray>().ArrayBuffer();
    int32_t nRequestID = info[1].As<Napi::Number>().Int32Value();
    CThostFtdcQryParkedOrderActionField *req =
        (CThostFtdcQryParkedOrderActionField *)ab.Data();
    api_->ReqQryParkedOrderAction(req, nRequestID);
  }

  void ReqQryTradingNotice(const CallbackInfo &info) {
    auto ab = info[0].As<Napi::TypedArray>().ArrayBuffer();
    int32_t nRequestID = info[1].As<Napi::Number>().Int32Value();
    CThostFtdcQryTradingNoticeField *req =
        (CThostFtdcQryTradingNoticeField *)ab.Data();
    api_->ReqQryTradingNotice(req, nRequestID);
  }

  void ReqQryBrokerTradingParams(const CallbackInfo &info) {
    auto ab = info[0].As<Napi::TypedArray>().ArrayBuffer();
    int32_t nRequestID = info[1].As<Napi::Number>().Int32Value();
    CThostFtdcQryBrokerTradingParamsField *req =
        (CThostFtdcQryBrokerTradingParamsField *)ab.Data();
    api_->ReqQryBrokerTradingParams(req, nRequestID);
  }

  void ReqQryBrokerTradingAlgos(const CallbackInfo &info) {
    auto ab = info[0].As<Napi::TypedArray>().ArrayBuffer();
    int32_t nRequestID = info[1].As<Napi::Number>().Int32Value();
    CThostFtdcQryBrokerTradingAlgosField *req =
        (CThostFtdcQryBrokerTradingAlgosField *)ab.Data();
    api_->ReqQryBrokerTradingAlgos(req, nRequestID);
  }

  void ReqQueryCFMMCTradingAccountToken(const CallbackInfo &info) {
    auto ab = info[0].As<Napi::TypedArray>().ArrayBuffer();
    int32_t nRequestID = info[1].As<Napi::Number>().Int32Value();
    CThostFtdcQueryCFMMCTradingAccountTokenField *req =
        (CThostFtdcQueryCFMMCTradingAccountTokenField *)ab.Data();
    api_->ReqQueryCFMMCTradingAccountToken(req, nRequestID);
  }

  void ReqFromBankToFutureByFuture(const CallbackInfo &info) {
    auto ab = info[0].As<Napi::TypedArray>().ArrayBuffer();
    int32_t nRequestID = info[1].As<Napi::Number>().Int32Value();
    CThostFtdcReqTransferField *req = (CThostFtdcReqTransferField *)ab.Data();
    api_->ReqFromBankToFutureByFuture(req, nRequestID);
  }

  void ReqFromFutureToBankByFuture(const CallbackInfo &info) {
    auto ab = info[0].As<Napi::TypedArray>().ArrayBuffer();
    int32_t nRequestID = info[1].As<Napi::Number>().Int32Value();
    CThostFtdcReqTransferField *req = (CThostFtdcReqTransferField *)ab.Data();
    api_->ReqFromFutureToBankByFuture(req, nRequestID);
  }

  void ReqQueryBankAccountMoneyByFuture(const CallbackInfo &info) {
    auto ab = info[0].As<Napi::TypedArray>().ArrayBuffer();
    int32_t nRequestID = info[1].As<Napi::Number>().Int32Value();
    CThostFtdcReqQueryAccountField *req =
        (CThostFtdcReqQueryAccountField *)ab.Data();
    api_->ReqQueryBankAccountMoneyByFuture(req, nRequestID);
  }

  //
  void OnFrontConnected() { callJS(new Message("OnFrontConnected", "", 0)); }
  void OnFrontDisconnected(int nReason) {
    callJS(new Message("OnFrontDisconnected", "", 0));
  }
  void OnHeartBeatWarning(int nTimeLapse) {
    callJS(new Message("OnHeartBeatWarning", "", 0));
  }
  void OnRspAuthenticate(CThostFtdcRspAuthenticateField *pRspAuthenticateField,
                         CThostFtdcRspInfoField *pRspInfo, int nRequestID,
                         bool bIsLast) {
    callJS(make_message("OnRspAuthenticate", pRspAuthenticateField, pRspInfo,
                        nRequestID, bIsLast));
  }
  void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin,
                      CThostFtdcRspInfoField *pRspInfo, int nRequestID,
                      bool bIsLast) {
    callJS(make_message("OnRspUserLogin", pRspUserLogin, pRspInfo, nRequestID,
                        bIsLast));
  }
  void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout,
                       CThostFtdcRspInfoField *pRspInfo, int nRequestID,
                       bool bIsLast) {
    callJS(make_message("OnRspUserLogout", pUserLogout, pRspInfo, nRequestID,
                        bIsLast));
  }
  void OnRspUserPasswordUpdate(
      CThostFtdcUserPasswordUpdateField *pUserPasswordUpdate,
      CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    callJS(make_message("OnRspUserPasswordUpdate", pUserPasswordUpdate,
                        pRspInfo, nRequestID, bIsLast));
  }
  void
  OnRspTradingAccountPasswordUpdate(CThostFtdcTradingAccountPasswordUpdateField
                                        *pTradingAccountPasswordUpdate,
                                    CThostFtdcRspInfoField *pRspInfo,
                                    int nRequestID, bool bIsLast) {
    callJS(make_message("OnRspTradingAccountPasswordUpdate",
                        pTradingAccountPasswordUpdate, pRspInfo, nRequestID,
                        bIsLast));
  }
  void OnRspUserAuthMethod(CThostFtdcRspUserAuthMethodField *pRspUserAuthMethod,
                           CThostFtdcRspInfoField *pRspInfo, int nRequestID,
                           bool bIsLast) {
    callJS(make_message("OnRspUserAuthMethod", pRspUserAuthMethod, pRspInfo,
                        nRequestID, bIsLast));
  }
  void OnRspGenUserCaptcha(CThostFtdcRspGenUserCaptchaField *pRspGenUserCaptcha,
                           CThostFtdcRspInfoField *pRspInfo, int nRequestID,
                           bool bIsLast) {
    callJS(make_message("OnRspGenUserCaptcha", pRspGenUserCaptcha, pRspInfo,
                        nRequestID, bIsLast));
  }
  void OnRspGenUserText(CThostFtdcRspGenUserTextField *pRspGenUserText,
                        CThostFtdcRspInfoField *pRspInfo, int nRequestID,
                        bool bIsLast) {
    callJS(make_message("OnRspGenUserText", pRspGenUserText, pRspInfo,
                        nRequestID, bIsLast));
  }
  void OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder,
                        CThostFtdcRspInfoField *pRspInfo, int nRequestID,
                        bool bIsLast) {
    callJS(make_message("OnRspOrderInsert", pInputOrder, pRspInfo, nRequestID,
                        bIsLast));
  }
  void OnRspParkedOrderInsert(CThostFtdcParkedOrderField *pParkedOrder,
                              CThostFtdcRspInfoField *pRspInfo, int nRequestID,
                              bool bIsLast) {
    callJS(make_message("OnRspParkedOrderInsert", pParkedOrder, pRspInfo,
                        nRequestID, bIsLast));
  }
  void
  OnRspParkedOrderAction(CThostFtdcParkedOrderActionField *pParkedOrderAction,
                         CThostFtdcRspInfoField *pRspInfo, int nRequestID,
                         bool bIsLast) {
    callJS(make_message("OnRspParkedOrderAction", pParkedOrderAction, pRspInfo,
                        nRequestID, bIsLast));
  }
  void OnRspOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction,
                        CThostFtdcRspInfoField *pRspInfo, int nRequestID,
                        bool bIsLast) {
    callJS(make_message("OnRspOrderAction", pInputOrderAction, pRspInfo,
                        nRequestID, bIsLast));
  }
  void OnRspQueryMaxOrderVolume(
      CThostFtdcQueryMaxOrderVolumeField *pQueryMaxOrderVolume,
      CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    callJS(make_message("OnRspQueryMaxOrderVolume", pQueryMaxOrderVolume,
                        pRspInfo, nRequestID, bIsLast));
  }
  void OnRspSettlementInfoConfirm(
      CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm,
      CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    callJS(make_message("OnRspSettlementInfoConfirm", pSettlementInfoConfirm,
                        pRspInfo, nRequestID, bIsLast));
  }
  void
  OnRspRemoveParkedOrder(CThostFtdcRemoveParkedOrderField *pRemoveParkedOrder,
                         CThostFtdcRspInfoField *pRspInfo, int nRequestID,
                         bool bIsLast) {
    callJS(make_message("OnRspRemoveParkedOrder", pRemoveParkedOrder, pRspInfo,
                        nRequestID, bIsLast));
  }
  void OnRspRemoveParkedOrderAction(
      CThostFtdcRemoveParkedOrderActionField *pRemoveParkedOrderAction,
      CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    callJS(make_message("OnRspRemoveParkedOrderAction",
                        pRemoveParkedOrderAction, pRspInfo, nRequestID,
                        bIsLast));
  }
  void OnRspExecOrderInsert(CThostFtdcInputExecOrderField *pInputExecOrder,
                            CThostFtdcRspInfoField *pRspInfo, int nRequestID,
                            bool bIsLast) {
    callJS(make_message("OnRspExecOrderInsert", pInputExecOrder, pRspInfo,
                        nRequestID, bIsLast));
  }
  void OnRspExecOrderAction(
      CThostFtdcInputExecOrderActionField *pInputExecOrderAction,
      CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    callJS(make_message("OnRspExecOrderAction", pInputExecOrderAction, pRspInfo,
                        nRequestID, bIsLast));
  }
  void OnRspForQuoteInsert(CThostFtdcInputForQuoteField *pInputForQuote,
                           CThostFtdcRspInfoField *pRspInfo, int nRequestID,
                           bool bIsLast) {
    callJS(make_message("OnRspForQuoteInsert", pInputForQuote, pRspInfo,
                        nRequestID, bIsLast));
  }
  void OnRspQuoteInsert(CThostFtdcInputQuoteField *pInputQuote,
                        CThostFtdcRspInfoField *pRspInfo, int nRequestID,
                        bool bIsLast) {
    callJS(make_message("OnRspQuoteInsert", pInputQuote, pRspInfo, nRequestID,
                        bIsLast));
  }
  void OnRspQuoteAction(CThostFtdcInputQuoteActionField *pInputQuoteAction,
                        CThostFtdcRspInfoField *pRspInfo, int nRequestID,
                        bool bIsLast) {
    callJS(make_message("OnRspQuoteAction", pInputQuoteAction, pRspInfo,
                        nRequestID, bIsLast));
  }
  void OnRspBatchOrderAction(
      CThostFtdcInputBatchOrderActionField *pInputBatchOrderAction,
      CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    callJS(make_message("OnRspBatchOrderAction", pInputBatchOrderAction,
                        pRspInfo, nRequestID, bIsLast));
  }
  void OnRspOptionSelfCloseInsert(
      CThostFtdcInputOptionSelfCloseField *pInputOptionSelfClose,
      CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    callJS(make_message("OnRspOptionSelfCloseInsert", pInputOptionSelfClose,
                        pRspInfo, nRequestID, bIsLast));
  }
  void OnRspOptionSelfCloseAction(
      CThostFtdcInputOptionSelfCloseActionField *pInputOptionSelfCloseAction,
      CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    callJS(make_message("OnRspOptionSelfCloseAction",
                        pInputOptionSelfCloseAction, pRspInfo, nRequestID,
                        bIsLast));
  }
  void OnRspCombActionInsert(CThostFtdcInputCombActionField *pInputCombAction,
                             CThostFtdcRspInfoField *pRspInfo, int nRequestID,
                             bool bIsLast) {
    callJS(make_message("OnRspCombActionInsert", pInputCombAction, pRspInfo,
                        nRequestID, bIsLast));
  }
  void OnRspQryOrder(CThostFtdcOrderField *pOrder,
                     CThostFtdcRspInfoField *pRspInfo, int nRequestID,
                     bool bIsLast) {
    callJS(
        make_message("OnRspQryOrder", pOrder, pRspInfo, nRequestID, bIsLast));
  }
  void OnRspQryTrade(CThostFtdcTradeField *pTrade,
                     CThostFtdcRspInfoField *pRspInfo, int nRequestID,
                     bool bIsLast) {
    callJS(
        make_message("OnRspQryTrade", pTrade, pRspInfo, nRequestID, bIsLast));
  }
  void
  OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition,
                           CThostFtdcRspInfoField *pRspInfo, int nRequestID,
                           bool bIsLast) {
    callJS(make_message("OnRspQryInvestorPosition", pInvestorPosition, pRspInfo,
                        nRequestID, bIsLast));
  }
  void OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount,
                              CThostFtdcRspInfoField *pRspInfo, int nRequestID,
                              bool bIsLast) {
    callJS(make_message("OnRspQryTradingAccount", pTradingAccount, pRspInfo,
                        nRequestID, bIsLast));
  }
  void OnRspQryInvestor(CThostFtdcInvestorField *pInvestor,
                        CThostFtdcRspInfoField *pRspInfo, int nRequestID,
                        bool bIsLast) {
    callJS(make_message("OnRspQryInvestor", pInvestor, pRspInfo, nRequestID,
                        bIsLast));
  }
  void OnRspQryTradingCode(CThostFtdcTradingCodeField *pTradingCode,
                           CThostFtdcRspInfoField *pRspInfo, int nRequestID,
                           bool bIsLast) {
    callJS(make_message("OnRspQryTradingCode", pTradingCode, pRspInfo,
                        nRequestID, bIsLast));
  }
  void OnRspQryInstrumentMarginRate(
      CThostFtdcInstrumentMarginRateField *pInstrumentMarginRate,
      CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    callJS(make_message("OnRspQryInstrumentMarginRate", pInstrumentMarginRate,
                        pRspInfo, nRequestID, bIsLast));
  }
  void OnRspQryInstrumentCommissionRate(
      CThostFtdcInstrumentCommissionRateField *pInstrumentCommissionRate,
      CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    callJS(make_message("OnRspQryInstrumentCommissionRate",
                        pInstrumentCommissionRate, pRspInfo, nRequestID,
                        bIsLast));
  }
  void OnRspQryExchange(CThostFtdcExchangeField *pExchange,
                        CThostFtdcRspInfoField *pRspInfo, int nRequestID,
                        bool bIsLast) {
    callJS(make_message("OnRspQryExchange", pExchange, pRspInfo, nRequestID,
                        bIsLast));
  }
  void OnRspQryProduct(CThostFtdcProductField *pProduct,
                       CThostFtdcRspInfoField *pRspInfo, int nRequestID,
                       bool bIsLast) {
    callJS(make_message("OnRspQryProduct", pProduct, pRspInfo, nRequestID,
                        bIsLast));
  }
  void OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument,
                          CThostFtdcRspInfoField *pRspInfo, int nRequestID,
                          bool bIsLast) {
    callJS(make_message("OnRspQryInstrument", pInstrument, pRspInfo, nRequestID,
                        bIsLast));
  }
  void OnRspQryDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData,
                               CThostFtdcRspInfoField *pRspInfo, int nRequestID,
                               bool bIsLast) {
    callJS(make_message("OnRspQryDepthMarketData", pDepthMarketData, pRspInfo,
                        nRequestID, bIsLast));
  }
  void OnRspQrySettlementInfo(CThostFtdcSettlementInfoField *pSettlementInfo,
                              CThostFtdcRspInfoField *pRspInfo, int nRequestID,
                              bool bIsLast) {
    callJS(make_message("OnRspQrySettlementInfo", pSettlementInfo, pRspInfo,
                        nRequestID, bIsLast));
  }
  void OnRspQryTransferBank(CThostFtdcTransferBankField *pTransferBank,
                            CThostFtdcRspInfoField *pRspInfo, int nRequestID,
                            bool bIsLast) {
    callJS(make_message("OnRspQryTransferBank", pTransferBank, pRspInfo,
                        nRequestID, bIsLast));
  }
  void OnRspQryInvestorPositionDetail(
      CThostFtdcInvestorPositionDetailField *pInvestorPositionDetail,
      CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    callJS(make_message("OnRspQryInvestorPositionDetail",
                        pInvestorPositionDetail, pRspInfo, nRequestID,
                        bIsLast));
  }
  void OnRspQryNotice(CThostFtdcNoticeField *pNotice,
                      CThostFtdcRspInfoField *pRspInfo, int nRequestID,
                      bool bIsLast) {
    callJS(
        make_message("OnRspQryNotice", pNotice, pRspInfo, nRequestID, bIsLast));
  }
  void OnRspQrySettlementInfoConfirm(
      CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm,
      CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    callJS(make_message("OnRspQrySettlementInfoConfirm", pSettlementInfoConfirm,
                        pRspInfo, nRequestID, bIsLast));
  }
  void OnRspQryInvestorPositionCombineDetail(
      CThostFtdcInvestorPositionCombineDetailField
          *pInvestorPositionCombineDetail,
      CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    callJS(make_message("OnRspQryInvestorPositionCombineDetail",
                        pInvestorPositionCombineDetail, pRspInfo, nRequestID,
                        bIsLast));
  }
  void OnRspQryCFMMCTradingAccountKey(
      CThostFtdcCFMMCTradingAccountKeyField *pCFMMCTradingAccountKey,
      CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    callJS(make_message("OnRspQryCFMMCTradingAccountKey",
                        pCFMMCTradingAccountKey, pRspInfo, nRequestID,
                        bIsLast));
  }
  void OnRspQryEWarrantOffset(CThostFtdcEWarrantOffsetField *pEWarrantOffset,
                              CThostFtdcRspInfoField *pRspInfo, int nRequestID,
                              bool bIsLast) {
    callJS(make_message("OnRspQryEWarrantOffset", pEWarrantOffset, pRspInfo,
                        nRequestID, bIsLast));
  }
  void OnRspQryInvestorProductGroupMargin(
      CThostFtdcInvestorProductGroupMarginField *pInvestorProductGroupMargin,
      CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    callJS(make_message("OnRspQryInvestorProductGroupMargin",
                        pInvestorProductGroupMargin, pRspInfo, nRequestID,
                        bIsLast));
  }
  void OnRspQryExchangeMarginRate(
      CThostFtdcExchangeMarginRateField *pExchangeMarginRate,
      CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    callJS(make_message("OnRspQryExchangeMarginRate", pExchangeMarginRate,
                        pRspInfo, nRequestID, bIsLast));
  }
  void OnRspQryExchangeMarginRateAdjust(
      CThostFtdcExchangeMarginRateAdjustField *pExchangeMarginRateAdjust,
      CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    callJS(make_message("OnRspQryExchangeMarginRateAdjust",
                        pExchangeMarginRateAdjust, pRspInfo, nRequestID,
                        bIsLast));
  }
  void OnRspQryExchangeRate(CThostFtdcExchangeRateField *pExchangeRate,
                            CThostFtdcRspInfoField *pRspInfo, int nRequestID,
                            bool bIsLast) {
    callJS(make_message("OnRspQryExchangeRate", pExchangeRate, pRspInfo,
                        nRequestID, bIsLast));
  }
  void OnRspQrySecAgentACIDMap(CThostFtdcSecAgentACIDMapField *pSecAgentACIDMap,
                               CThostFtdcRspInfoField *pRspInfo, int nRequestID,
                               bool bIsLast) {
    callJS(make_message("OnRspQrySecAgentACIDMap", pSecAgentACIDMap, pRspInfo,
                        nRequestID, bIsLast));
  }
  void OnRspQryProductExchRate(CThostFtdcProductExchRateField *pProductExchRate,
                               CThostFtdcRspInfoField *pRspInfo, int nRequestID,
                               bool bIsLast) {
    callJS(make_message("OnRspQryProductExchRate", pProductExchRate, pRspInfo,
                        nRequestID, bIsLast));
  }
  void OnRspQryProductGroup(CThostFtdcProductGroupField *pProductGroup,
                            CThostFtdcRspInfoField *pRspInfo, int nRequestID,
                            bool bIsLast) {
    callJS(make_message("OnRspQryProductGroup", pProductGroup, pRspInfo,
                        nRequestID, bIsLast));
  }
  void OnRspQryMMInstrumentCommissionRate(
      CThostFtdcMMInstrumentCommissionRateField *pMMInstrumentCommissionRate,
      CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    callJS(make_message("OnRspQryMMInstrumentCommissionRate",
                        pMMInstrumentCommissionRate, pRspInfo, nRequestID,
                        bIsLast));
  }
  void OnRspQryMMOptionInstrCommRate(
      CThostFtdcMMOptionInstrCommRateField *pMMOptionInstrCommRate,
      CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    callJS(make_message("OnRspQryMMOptionInstrCommRate", pMMOptionInstrCommRate,
                        pRspInfo, nRequestID, bIsLast));
  }
  void OnRspQryInstrumentOrderCommRate(
      CThostFtdcInstrumentOrderCommRateField *pInstrumentOrderCommRate,
      CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    callJS(make_message("OnRspQryInstrumentOrderCommRate",
                        pInstrumentOrderCommRate, pRspInfo, nRequestID,
                        bIsLast));
  }
  void
  OnRspQrySecAgentTradingAccount(CThostFtdcTradingAccountField *pTradingAccount,
                                 CThostFtdcRspInfoField *pRspInfo,
                                 int nRequestID, bool bIsLast) {
    callJS(make_message("OnRspQrySecAgentTradingAccount", pTradingAccount,
                        pRspInfo, nRequestID, bIsLast));
  }
  void OnRspQrySecAgentCheckMode(
      CThostFtdcSecAgentCheckModeField *pSecAgentCheckMode,
      CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    callJS(make_message("OnRspQrySecAgentCheckMode", pSecAgentCheckMode,
                        pRspInfo, nRequestID, bIsLast));
  }
  void OnRspQrySecAgentTradeInfo(
      CThostFtdcSecAgentTradeInfoField *pSecAgentTradeInfo,
      CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    callJS(make_message("OnRspQrySecAgentTradeInfo", pSecAgentTradeInfo,
                        pRspInfo, nRequestID, bIsLast));
  }
  void OnRspQryOptionInstrTradeCost(
      CThostFtdcOptionInstrTradeCostField *pOptionInstrTradeCost,
      CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    callJS(make_message("OnRspQryOptionInstrTradeCost", pOptionInstrTradeCost,
                        pRspInfo, nRequestID, bIsLast));
  }
  void OnRspQryOptionInstrCommRate(
      CThostFtdcOptionInstrCommRateField *pOptionInstrCommRate,
      CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    callJS(make_message("OnRspQryOptionInstrCommRate", pOptionInstrCommRate,
                        pRspInfo, nRequestID, bIsLast));
  }
  void OnRspQryExecOrder(CThostFtdcExecOrderField *pExecOrder,
                         CThostFtdcRspInfoField *pRspInfo, int nRequestID,
                         bool bIsLast) {
    callJS(make_message("OnRspQryExecOrder", pExecOrder, pRspInfo, nRequestID,
                        bIsLast));
  }
  void OnRspQryForQuote(CThostFtdcForQuoteField *pForQuote,
                        CThostFtdcRspInfoField *pRspInfo, int nRequestID,
                        bool bIsLast) {
    callJS(make_message("OnRspQryForQuote", pForQuote, pRspInfo, nRequestID,
                        bIsLast));
  }
  void OnRspQryQuote(CThostFtdcQuoteField *pQuote,
                     CThostFtdcRspInfoField *pRspInfo, int nRequestID,
                     bool bIsLast) {
    callJS(
        make_message("OnRspQryQuote", pQuote, pRspInfo, nRequestID, bIsLast));
  }
  void OnRspQryOptionSelfClose(CThostFtdcOptionSelfCloseField *pOptionSelfClose,
                               CThostFtdcRspInfoField *pRspInfo, int nRequestID,
                               bool bIsLast) {
    callJS(make_message("OnRspQryOptionSelfClose", pOptionSelfClose, pRspInfo,
                        nRequestID, bIsLast));
  }
  void OnRspQryInvestUnit(CThostFtdcInvestUnitField *pInvestUnit,
                          CThostFtdcRspInfoField *pRspInfo, int nRequestID,
                          bool bIsLast) {
    callJS(make_message("OnRspQryInvestUnit", pInvestUnit, pRspInfo, nRequestID,
                        bIsLast));
  }
  void OnRspQryCombInstrumentGuard(
      CThostFtdcCombInstrumentGuardField *pCombInstrumentGuard,
      CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    callJS(make_message("OnRspQryCombInstrumentGuard", pCombInstrumentGuard,
                        pRspInfo, nRequestID, bIsLast));
  }
  void OnRspQryCombAction(CThostFtdcCombActionField *pCombAction,
                          CThostFtdcRspInfoField *pRspInfo, int nRequestID,
                          bool bIsLast) {
    callJS(make_message("OnRspQryCombAction", pCombAction, pRspInfo, nRequestID,
                        bIsLast));
  }
  void OnRspQryTransferSerial(CThostFtdcTransferSerialField *pTransferSerial,
                              CThostFtdcRspInfoField *pRspInfo, int nRequestID,
                              bool bIsLast) {
    callJS(make_message("OnRspQryTransferSerial", pTransferSerial, pRspInfo,
                        nRequestID, bIsLast));
  }
  void OnRspQryAccountregister(CThostFtdcAccountregisterField *pAccountregister,
                               CThostFtdcRspInfoField *pRspInfo, int nRequestID,
                               bool bIsLast) {
    callJS(make_message("OnRspQryAccountregister", pAccountregister, pRspInfo,
                        nRequestID, bIsLast));
  }
  void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID,
                  bool bIsLast) {
    callJS(make_message("OnRspError", pRspInfo, pRspInfo, nRequestID, bIsLast));
  }
  void OnRtnOrder(CThostFtdcOrderField *pOrder) {
    callJS(make_message("OnRtnOrder", pOrder));
  }
  void OnRtnTrade(CThostFtdcTradeField *pTrade) {
    callJS(make_message("OnRtnTrade", pTrade));
  }
  void OnErrRtnOrderInsert(CThostFtdcInputOrderField *pInputOrder,
                           CThostFtdcRspInfoField *pRspInfo) {
    callJS(make_message("OnErrRtnOrderInsert", pInputOrder, pRspInfo));
  }
  void OnErrRtnOrderAction(CThostFtdcOrderActionField *pOrderAction,
                           CThostFtdcRspInfoField *pRspInfo) {
    callJS(make_message("OnErrRtnOrderAction", pOrderAction, pRspInfo));
  }
  void
  OnRtnInstrumentStatus(CThostFtdcInstrumentStatusField *pInstrumentStatus) {
    callJS(make_message("OnRtnInstrumentStatus", pInstrumentStatus));
  }
  void OnRtnBulletin(CThostFtdcBulletinField *pBulletin) {
    callJS(make_message("OnRtnBulletin", pBulletin));
  }
  void
  OnRtnTradingNotice(CThostFtdcTradingNoticeInfoField *pTradingNoticeInfo) {
    callJS(make_message("OnRtnTradingNotice", pTradingNoticeInfo));
  }
  void OnRtnErrorConditionalOrder(
      CThostFtdcErrorConditionalOrderField *pErrorConditionalOrder) {
    callJS(make_message("OnRtnErrorConditionalOrder", pErrorConditionalOrder));
  }
  void OnRtnExecOrder(CThostFtdcExecOrderField *pExecOrder) {
    callJS(make_message("OnRtnExecOrder", pExecOrder));
  }
  void OnErrRtnExecOrderInsert(CThostFtdcInputExecOrderField *pInputExecOrder,
                               CThostFtdcRspInfoField *pRspInfo) {
    callJS(make_message("OnErrRtnExecOrderInsert", pInputExecOrder, pRspInfo));
  }
  void OnErrRtnExecOrderAction(CThostFtdcExecOrderActionField *pExecOrderAction,
                               CThostFtdcRspInfoField *pRspInfo) {
    callJS(make_message("OnErrRtnExecOrderAction", pExecOrderAction, pRspInfo));
  }
  void OnErrRtnForQuoteInsert(CThostFtdcInputForQuoteField *pInputForQuote,
                              CThostFtdcRspInfoField *pRspInfo) {
    callJS(make_message("OnErrRtnForQuoteInsert", pInputForQuote, pRspInfo));
  }
  void OnRtnQuote(CThostFtdcQuoteField *pQuote) {
    callJS(make_message("OnRtnQuote", pQuote));
  }
  void OnErrRtnQuoteInsert(CThostFtdcInputQuoteField *pInputQuote,
                           CThostFtdcRspInfoField *pRspInfo) {
    callJS(make_message("OnErrRtnQuoteInsert", pInputQuote, pRspInfo));
  }
  void OnErrRtnQuoteAction(CThostFtdcQuoteActionField *pQuoteAction,
                           CThostFtdcRspInfoField *pRspInfo) {
    callJS(make_message("OnErrRtnQuoteAction", pQuoteAction, pRspInfo));
  }
  void OnRtnForQuoteRsp(CThostFtdcForQuoteRspField *pForQuoteRsp) {
    callJS(make_message("OnRtnForQuoteRsp", pForQuoteRsp));
  }
  void OnRtnCFMMCTradingAccountToken(
      CThostFtdcCFMMCTradingAccountTokenField *pCFMMCTradingAccountToken) {
    callJS(make_message("OnRtnCFMMCTradingAccountToken",
                        pCFMMCTradingAccountToken));
  }
  void
  OnErrRtnBatchOrderAction(CThostFtdcBatchOrderActionField *pBatchOrderAction,
                           CThostFtdcRspInfoField *pRspInfo) {
    callJS(
        make_message("OnErrRtnBatchOrderAction", pBatchOrderAction, pRspInfo));
  }
  void OnRtnOptionSelfClose(CThostFtdcOptionSelfCloseField *pOptionSelfClose) {
    callJS(make_message("OnRtnOptionSelfClose", pOptionSelfClose));
  }
  void OnErrRtnOptionSelfCloseInsert(
      CThostFtdcInputOptionSelfCloseField *pInputOptionSelfClose,
      CThostFtdcRspInfoField *pRspInfo) {
    callJS(make_message("OnErrRtnOptionSelfCloseInsert", pInputOptionSelfClose,
                        pRspInfo));
  }
  void OnErrRtnOptionSelfCloseAction(
      CThostFtdcOptionSelfCloseActionField *pOptionSelfCloseAction,
      CThostFtdcRspInfoField *pRspInfo) {
    callJS(make_message("OnErrRtnOptionSelfCloseAction", pOptionSelfCloseAction,
                        pRspInfo));
  }
  void OnRtnCombAction(CThostFtdcCombActionField *pCombAction) {
    callJS(make_message("OnRtnCombAction", pCombAction));
  }
  void
  OnErrRtnCombActionInsert(CThostFtdcInputCombActionField *pInputCombAction,
                           CThostFtdcRspInfoField *pRspInfo) {
    callJS(
        make_message("OnErrRtnCombActionInsert", pInputCombAction, pRspInfo));
  }
  void OnRspQryContractBank(CThostFtdcContractBankField *pContractBank,
                            CThostFtdcRspInfoField *pRspInfo, int nRequestID,
                            bool bIsLast) {
    callJS(make_message("OnRspQryContractBank", pContractBank, pRspInfo,
                        nRequestID, bIsLast));
  }
  void OnRspQryParkedOrder(CThostFtdcParkedOrderField *pParkedOrder,
                           CThostFtdcRspInfoField *pRspInfo, int nRequestID,
                           bool bIsLast) {
    callJS(make_message("OnRspQryParkedOrder", pParkedOrder, pRspInfo,
                        nRequestID, bIsLast));
  }
  void OnRspQryParkedOrderAction(
      CThostFtdcParkedOrderActionField *pParkedOrderAction,
      CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    callJS(make_message("OnRspQryParkedOrderAction", pParkedOrderAction,
                        pRspInfo, nRequestID, bIsLast));
  }
  void OnRspQryTradingNotice(CThostFtdcTradingNoticeField *pTradingNotice,
                             CThostFtdcRspInfoField *pRspInfo, int nRequestID,
                             bool bIsLast) {
    callJS(make_message("OnRspQryTradingNotice", pTradingNotice, pRspInfo,
                        nRequestID, bIsLast));
  }
  void OnRspQryBrokerTradingParams(
      CThostFtdcBrokerTradingParamsField *pBrokerTradingParams,
      CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    callJS(make_message("OnRspQryBrokerTradingParams", pBrokerTradingParams,
                        pRspInfo, nRequestID, bIsLast));
  }
  void OnRspQryBrokerTradingAlgos(
      CThostFtdcBrokerTradingAlgosField *pBrokerTradingAlgos,
      CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    callJS(make_message("OnRspQryBrokerTradingAlgos", pBrokerTradingAlgos,
                        pRspInfo, nRequestID, bIsLast));
  }
  void OnRspQueryCFMMCTradingAccountToken(
      CThostFtdcQueryCFMMCTradingAccountTokenField
          *pQueryCFMMCTradingAccountToken,
      CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    callJS(make_message("OnRspQueryCFMMCTradingAccountToken",
                        pQueryCFMMCTradingAccountToken, pRspInfo, nRequestID,
                        bIsLast));
  }
  void OnRtnFromBankToFutureByBank(CThostFtdcRspTransferField *pRspTransfer) {
    callJS(make_message("OnRtnFromBankToFutureByBank", pRspTransfer));
  }
  void OnRtnFromFutureToBankByBank(CThostFtdcRspTransferField *pRspTransfer) {
    callJS(make_message("OnRtnFromFutureToBankByBank", pRspTransfer));
  }
  void OnRtnRepealFromBankToFutureByBank(CThostFtdcRspRepealField *pRspRepeal) {
    callJS(make_message("OnRtnRepealFromBankToFutureByBank", pRspRepeal));
  }
  void OnRtnRepealFromFutureToBankByBank(CThostFtdcRspRepealField *pRspRepeal) {
    callJS(make_message("OnRtnRepealFromFutureToBankByBank", pRspRepeal));
  }
  void OnRtnFromBankToFutureByFuture(CThostFtdcRspTransferField *pRspTransfer) {
    callJS(make_message("OnRtnFromBankToFutureByFuture", pRspTransfer));
  }
  void OnRtnFromFutureToBankByFuture(CThostFtdcRspTransferField *pRspTransfer) {
    callJS(make_message("OnRtnFromFutureToBankByFuture", pRspTransfer));
  }
  void OnRtnRepealFromBankToFutureByFutureManual(
      CThostFtdcRspRepealField *pRspRepeal) {
    callJS(
        make_message("OnRtnRepealFromBankToFutureByFutureManual", pRspRepeal));
  }
  void OnRtnRepealFromFutureToBankByFutureManual(
      CThostFtdcRspRepealField *pRspRepeal) {
    callJS(
        make_message("OnRtnRepealFromFutureToBankByFutureManual", pRspRepeal));
  }
  void OnRtnQueryBankBalanceByFuture(
      CThostFtdcNotifyQueryAccountField *pNotifyQueryAccount) {
    callJS(make_message("OnRtnQueryBankBalanceByFuture", pNotifyQueryAccount));
  }
  void OnErrRtnBankToFutureByFuture(CThostFtdcReqTransferField *pReqTransfer,
                                    CThostFtdcRspInfoField *pRspInfo) {
    callJS(
        make_message("OnErrRtnBankToFutureByFuture", pReqTransfer, pRspInfo));
  }
  void OnErrRtnFutureToBankByFuture(CThostFtdcReqTransferField *pReqTransfer,
                                    CThostFtdcRspInfoField *pRspInfo) {
    callJS(
        make_message("OnErrRtnFutureToBankByFuture", pReqTransfer, pRspInfo));
  }
  void
  OnErrRtnRepealBankToFutureByFutureManual(CThostFtdcReqRepealField *pReqRepeal,
                                           CThostFtdcRspInfoField *pRspInfo) {
    callJS(make_message("OnErrRtnRepealBankToFutureByFutureManual", pReqRepeal,
                        pRspInfo));
  }
  void
  OnErrRtnRepealFutureToBankByFutureManual(CThostFtdcReqRepealField *pReqRepeal,
                                           CThostFtdcRspInfoField *pRspInfo) {
    callJS(make_message("OnErrRtnRepealFutureToBankByFutureManual", pReqRepeal,
                        pRspInfo));
  }
  void OnErrRtnQueryBankBalanceByFuture(
      CThostFtdcReqQueryAccountField *pReqQueryAccount,
      CThostFtdcRspInfoField *pRspInfo) {
    callJS(make_message("OnErrRtnQueryBankBalanceByFuture", pReqQueryAccount,
                        pRspInfo));
  }
  void
  OnRtnRepealFromBankToFutureByFuture(CThostFtdcRspRepealField *pRspRepeal) {
    callJS(make_message("OnRtnRepealFromBankToFutureByFuture", pRspRepeal));
  }
  void
  OnRtnRepealFromFutureToBankByFuture(CThostFtdcRspRepealField *pRspRepeal) {
    callJS(make_message("OnRtnRepealFromFutureToBankByFuture", pRspRepeal));
  }
  void OnRspFromBankToFutureByFuture(CThostFtdcReqTransferField *pReqTransfer,
                                     CThostFtdcRspInfoField *pRspInfo,
                                     int nRequestID, bool bIsLast) {
    callJS(make_message("OnRspFromBankToFutureByFuture", pReqTransfer, pRspInfo,
                        nRequestID, bIsLast));
  }
  void OnRspFromFutureToBankByFuture(CThostFtdcReqTransferField *pReqTransfer,
                                     CThostFtdcRspInfoField *pRspInfo,
                                     int nRequestID, bool bIsLast) {
    callJS(make_message("OnRspFromFutureToBankByFuture", pReqTransfer, pRspInfo,
                        nRequestID, bIsLast));
  }
  void OnRspQueryBankAccountMoneyByFuture(
      CThostFtdcReqQueryAccountField *pReqQueryAccount,
      CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    callJS(make_message("OnRspQueryBankAccountMoneyByFuture", pReqQueryAccount,
                        pRspInfo, nRequestID, bIsLast));
  }
  void OnRtnOpenAccountByBank(CThostFtdcOpenAccountField *pOpenAccount) {
    callJS(make_message("OnRtnOpenAccountByBank", pOpenAccount));
  }
  void OnRtnCancelAccountByBank(CThostFtdcCancelAccountField *pCancelAccount) {
    callJS(make_message("OnRtnCancelAccountByBank", pCancelAccount));
  }
  void OnRtnChangeAccountByBank(CThostFtdcChangeAccountField *pChangeAccount) {
    callJS(make_message("OnRtnChangeAccountByBank", pChangeAccount));
  }
};

} // namespace addon

#endif