#include "addons/binary/BinaryAddonManager.h"

int main() {
  ADDON::CBinaryAddonManager* manager = new ADDON::CBinaryAddonManager;
  fprintf(stdout, "Binary EXE addon test mananger started\n");
  manager->StartManager();
  sleep(20);
  manager->StopManager();
  fprintf(stdout, "Binary EXE addon test mananger stopped\n");
  delete manager;
}
