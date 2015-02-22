/**
This file is part of PROGRAM
Copyright (C) 2014-2015 Frantisek Uhrecky <frantisek.uhrecky[what here]gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef BPU_CODECTX_H
#define BPU_CODECTX_H

#include <stdint.h>

#include <bitpunch/math/gf2.h>
#include <bitpunch/math/gf2x.h>
#include <bitpunch/math/mathctx.h>

// addiotional codes
#include <bitpunch/code/goppa/goppatypes.h>

/// Possible types of codes
typedef enum _BPU_EN_Code_Types {
	BPU_EN_CODE_GOPPA
	// HERE you can add your code type
}BPU_EN_Code_Types;

typedef struct _BPU_T_Code_Ctx {
	BPU_EN_Code_Types type;
	int (* _encode)(BPU_T_Vector_GF2 *out, const BPU_T_Vector_GF2 *in, const struct _BPU_T_Code_Ctx *ctx); ///< This is reference to encode function. It will be set in BPU_codeInitCtx
	int (* _decode)(BPU_T_Vector_GF2 *out, const BPU_T_Vector_GF2 *in, const struct _BPU_T_Code_Ctx *ctx); ///< This is reference to decode function. It will be set in BPU_codeInitCtx
	BPU_T_Math_Ctx *math_ctx;
	uint16_t code_len;
	uint16_t msg_len;
	uint8_t t; ///< Error code correction capability

	union {
		BPU_T_Goppa_Spec *goppa;
		// HERE you add your code spec structure
	}code_spec; ///< Code specific structure, like generator matrix, control matrix, gen. poly ...
}BPU_T_Code_Ctx;

/// Initialize (register) code functions encode, decode and code spec structure based on code type.
int BPU_codeInitCtx(BPU_T_Code_Ctx *ctx, const uint16_t m, const uint16_t t, const BPU_EN_Code_Types type);

int BPU_codeInitMathCtx(BPU_T_Math_Ctx *ctx, const uint16_t m, const uint16_t t);

void BPU_codeFreeCtx(BPU_T_Code_Ctx *ctx);
#endif // BPU_CODECTX_H