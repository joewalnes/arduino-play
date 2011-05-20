#pragma once

struct IrCommand {
};

struct NecSingleCommand : public IrCommand {
// 32 bits
};

struct NecDoubleCommand : public IrCommand {
// 32 bits
};

class IrController {

  public:

    IrCommand nec(int code) {
      return NecSingleCommand();
    }

    IrCommand nec(int code1, int code2) {
      return NecDoubleCommand();
    }

    void send(IrCommand command) {
    }

} ir;
