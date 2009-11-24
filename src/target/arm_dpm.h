/*
 * Copyright (C) 2009 by David Brownell
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the
 * Free Software Foundation, Inc.,
 * 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

#ifndef __ARM_DPM_H
#define __ARM_DPM_H

/**
 * @file
 * This is the interface to the Debug Programmers Model for ARMv6 and
 * ARMv7 processors.  ARMv6 processors (such as ARM11xx implementations)
 * introduced a model which became part of the ARMv7-AR architecture
 * which is most familiar through the Cortex-A series parts.  While
 * specific details differ (like how to write the instruction register),
 * the high level models easily support shared code because those
 * registers are compatible.
 */

/**
 * This wraps an implementation of DPM primitives.  Each interface
 * provider supplies a structure like this, which is the glue between
 * upper level code and the lower level hardware access.
 *
 * It is a PRELIMINARY AND INCOMPLETE set of primitives, starting with
 * support for CPU register access.
 */
struct arm_dpm {
	struct arm *arm;

	/** Cache of DIDR */
	uint32_t didr;

	/** Invoke before a series of instruction operations */
	int (*prepare)(struct arm_dpm *);

	/** Invoke after a series of instruction operations */
	int (*finish)(struct arm_dpm *);

	/* WRITE TO CPU */

	/** Runs one instruction, writing data to DCC before execution. */
	int (*instr_write_data_dcc)(struct arm_dpm *,
			uint32_t opcode, uint32_t data);

	/** Runs one instruction, writing data to R0 before execution. */
	int (*instr_write_data_r0)(struct arm_dpm *,
			uint32_t opcode, uint32_t data);

	/* READ FROM CPU */

	/** Runs one instruction, reading data from dcc after execution. */
	int (*instr_read_data_dcc)(struct arm_dpm *,
			uint32_t opcode, uint32_t *data);

	/** Runs one instruction, reading data from r0 after execution. */
	int (*instr_read_data_r0)(struct arm_dpm *,
			uint32_t opcode, uint32_t *data);

	// FIXME -- add breakpoint support

	// FIXME -- add watchpoint support (including context-sensitive ones)

	// FIXME -- read/write DCSR methods and symbols
};

int arm_dpm_setup(struct arm_dpm *dpm);
int arm_dpm_reinitialize(struct arm_dpm *dpm);

int arm_dpm_read_current_registers(struct arm_dpm *);
int arm_dpm_write_dirty_registers(struct arm_dpm *);

#endif /* __ARM_DPM_H */