/* radare - LGPL - Copyright 2012-2018 - pancake */

#include <stdio.h>
#include <string.h>
#include <rz_types.h>
#include <rz_lib.h>
#include <rz_asm.h>

#include <v850_disas.h>

static int disassemble(RzAsm *a, RzAsmOp *op, const ut8 *buf, int len) {
	struct v850_cmd cmd = {
		.addr = a->pc,
		.instr = "",
		.operands = ""
	};
	if (len < 2) {
		return -1;
	}
	int ret = v850_decode_command (buf, len, &cmd);
	if (ret > 0) {
		rz_asm_op_set_asm (op, sdb_fmt ("%s %s", cmd.instr, cmd.operands));
	}
	return op->size = ret;
}

RzAsmPlugin rz_asm_plugin_v850 = {
	.name = "v850",
	.license = "LGPL3",
	.desc = "v850 disassembly plugin",
	.arch = "v850",
	.bits = 32,
	.endian = R_SYS_ENDIAN_LITTLE,
	.disassemble = &disassemble
};

#ifndef R2_PLUGIN_INCORE
RZ_API RzLibStruct radare_plugin = {
	.type = R_LIB_TYPE_ASM,
	.data = &rz_asm_plugin_v850,
	.version = R2_VERSION
};
#endif