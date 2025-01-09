#ifndef CATMshCVMSpa_h
#define CATMshCVMSpa_h

#include <iostream>

#include "CATIMshCVMSpa.h"

/*
 * This is a demonstrator of the CVMSpa toolkit.
 * It is for test purpose only and should not be integrated directly.
 * Please refer to : CATIMshCVMSpa.
 * DEPRECATED : inheritance from this class is deprecated
 */
class ExportedByCATMshCVMSpa CATMshCVMSpa
    : public CATIMshCVMSpa<CATMshCVMKernel::KernelI32> {
public:
    explicit CATMshCVMSpa() noexcept {}

    virtual ~CATMshCVMSpa() {}

    virtual void MessageCallback(CATMshMessage& msg) const override {
        /*
         * Extract all the data from the CATMshMessage
         */
        auto code(msg.GetCode());
        auto origin(msg.GetOrigin());
        std::string desc(msg.GetDescription());
        auto severity(msg.GetSeverity());
        int* brkIData;
        double* brkDData;
        auto nIData = msg.GetAttachedData(&brkIData);
        auto nDData = msg.GetAttachedData(&brkDData);
        /*
         * Process the data ...
         */
        std::cout << desc << std::endl;
    }

    virtual int InterruptCallback() override {
        /*
         * Here you can send an interrupt code to the mesher
         */
        return CATMSH_INTERRUPT_CONTINUE;
    };

    virtual bool IsDebug() const override {
        /*
         * Sets whether to activate the CVM debug mode or not
         */
        return false;
    }
};

#endif
