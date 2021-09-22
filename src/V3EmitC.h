// -*- mode: C++; c-file-style: "cc-mode" -*-
//*************************************************************************
// DESCRIPTION: Verilator: Emit C++ code for module tree
//
// Code available from: https://verilator.org
//
//*************************************************************************
//
// Copyright 2003-2021 by Wilson Snyder. This program is free software; you
// can redistribute it and/or modify it under the terms of either the GNU
// Lesser General Public License Version 3 or the Perl Artistic License
// Version 2.0.
// SPDX-License-Identifier: LGPL-3.0-only OR Artistic-2.0
//
//*************************************************************************

#ifndef VERILATOR_V3EMITC_H_
#define VERILATOR_V3EMITC_H_

#include "config_build.h"
#include "verilatedos.h"

#include "V3Error.h"
#include "V3Ast.h"

//============================================================================

class V3EmitC final {
    // RTLflow leverage datatype to get size, so that we can allocate GPU memory
    using CData = vluint8_t;  ///< Data representing 'bit' of 1-8 packed bits
    using SData = vluint16_t;  ///< Data representing 'bit' of 9-16 packed bits
    using IData = vluint32_t;  ///< Data representing 'bit' of 17-32 packed bits
    using QData = vluint64_t;  ///< Data representing 'bit' of 33-64 packed bits
    using EData = vluint32_t;  ///< Data representing one element of WData array
    using WData = EData;  ///< Data representing >64 packed bits (used as pointer)
public:
    static void emitc();
    static void emitcInlines();
    static void emitcSyms(bool dpiHdrOnly = false);
    static void emitcTrace();
    static void emitcFiles();

    // RTLflow
    static void emitRTLflowInt(size_t cuda_cmem_size, size_t cuda_smem_size, size_t cuda_imem_size,
                               size_t cuda_qmem_size);
    static void emitRTLflowImp();

    // static std::tuple<size_t, size_t, size_t, size_t> cuda_mem();
};

#endif  // Guard
