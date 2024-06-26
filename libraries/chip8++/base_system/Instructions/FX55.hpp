#ifndef _CHIP8_INSTRUCTIONS_FX55_HPP_
#define _CHIP8_INSTRUCTIONS_FX55_HPP_

#include "Instruction.hpp"

namespace CHIP8::Instructions
{
	/**
	 * @brief Store registers V0 through VX in memory starting at location I
	 * 
	 * This class represents the instruction to store registers V0 through VX in memory starting at location I.
	 */
	class IFX55 : 
		public Instruction,
		public std::enable_shared_from_this<IFX55>
	{
		uint8_t registerVX;
	public:
		/**
		 * @brief Execute the instruction to store registers V0 through VX in memory starting at location I
		 * 
		 * This function stores registers V0 through VX in memory starting at location I.
		 * 
		 * @param CPU 	Pointer to the CPU object
		 * @return bool (true) : Notify the CPU that the instruction was executed
		 */
		bool Execute(CPU *cpu) override {
			for (uint8_t i = 0; i <= registerVX; i++) {
				cpu->GetMemory()->SetByte(cpu->GetIndex() + i, cpu->GetRegister(i));
			}

			if (cpu->GetQuirks().MemoryLeaveIunchanged == false)
			{
				if (cpu->GetQuirks().MemoryIncrementByX)
				{
					cpu->SetIndex(cpu->GetIndex() + registerVX);
				}
				else
				{
					cpu->SetIndex(cpu->GetIndex() + registerVX + 1);
				}
			}
			
			return true;
		};

		/**
		 * @brief Returns the mnemonic for the store registers V0 through VX in memory starting at location I instruction
		 * 
		 * @return std::string (LD [I], Vx) : Returns the mnemonic for the store registers V0 through VX in memory starting at location I instruction
		 */
		std::string GetMnemonic() override {
			return std::format("LD [I], V{:X}", registerVX);
		}

		/**
		 * @brief Returns the description for the store registers V0 through VX in memory starting at location I instruction
		 * 
		 * @return std::string (Store registers V0 through Vx in memory starting at location I) : Returns the description for the store registers V0 through VX in memory starting at location I instruction
		 */
		std::string GetDescription() override {
			return std::format("Store registers V0 through V{:X} in memory starting at location I", registerVX);
		}

		/**
		 * @brief Returns the opcode and mask for the store registers V0 through VX in memory starting at location I instruction
		 * 
		 * @return InstructionInfo_t (0xF055, 0xF0FF) : Returns the opcode and mask for the store registers V0 through VX in memory starting at location I instruction
		 */
		InstructionInfo_t GetInfo() override {
			return {0xF055, 0xF0FF};
		}

		/**
		 * @brief Update the instruction with the opcode
		 * 
		 * This function updates the instruction with the opcode.
		 * 
		 * @param opcode Opcode to be used for the instruction
		 * @return Instruction* Pointer to the instruction
		 */
		std::shared_ptr<Instructions::Instruction> Update(uint16_t opcode) override {
			registerVX = (opcode & 0x0F00) >> 8;
			return shared_from_this();
		}
	};
}

#endif /* _CHIP8_INSTRUCTIONS_FX55_HPP_ */