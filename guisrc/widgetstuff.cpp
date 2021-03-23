#include "widgetstuff.h"
#include "window.h"
#include "./ui_window.h"

Window::Window(QWidget *parent) : QMainWindow(parent), ui(new Ui::Window) {
  ui->setupUi(this);
  QObject::connect(ui->ISOBrowse, SIGNAL(clicked()), this, SLOT(ISOBrowser()));
  QObject::connect(ui->replaceBrowse, SIGNAL(clicked()), this,
                   SLOT(replacementBrowser()));
  QObject::connect(ui->importButton, SIGNAL(clicked()), this, SLOT(import()));
  //COMBOBOX SETUP
  //god this is messy, but it'll have to do!
  //DATA
  ui->DirSelect->addItem("DATA/LOGO.INT");
  ui->DirSelect->addItem("DATA/ST01GM0.INT");
  ui->DirSelect->addItem("DATA/ST01HK0.INT");
  ui->DirSelect->addItem("DATA/ST02GM0.INT");
  ui->DirSelect->addItem("DATA/ST02HK0.INT");
  ui->DirSelect->addItem("DATA/ST03GM0.INT");
  ui->DirSelect->addItem("DATA/ST03HK0.INT");
  ui->DirSelect->addItem("DATA/ST04GM0.INT");
  ui->DirSelect->addItem("DATA/ST04HK0.INT");
  ui->DirSelect->addItem("DATA/ST05GM0.INT");
  ui->DirSelect->addItem("DATA/ST05HK0.INT");
  ui->DirSelect->addItem("DATA/ST06GM0.INT");
  ui->DirSelect->addItem("DATA/ST06HK0.INT");
  ui->DirSelect->addItem("DATA/ST07GM0.INT");
  ui->DirSelect->addItem("DATA/ST07HK0.INT");
  ui->DirSelect->addItem("DATA/ST01GM0.INT");
  ui->DirSelect->addItem("DATA/ST08GM0.INT");
  ui->DirSelect->addItem("DATA/STBN.INT");
  ui->DirSelect->addItem("DATA/STMENU.INT");
  ui->DirSelect->addItem("DATA/TITLE.INT");
  ui->DirSelect->addItem("DATA/VS01VS0.INT");
  ui->DirSelect->addItem("DATA/VS02VS0.INT");
  ui->DirSelect->addItem("DATA/VS03VS0.INT");
  ui->DirSelect->addItem("DATA/VS04VS0.INT");
  ui->DirSelect->addItem("DATA/VS05VS0.INT");
  ui->DirSelect->addItem("DATA/VS06VS0.INT");
  ui->DirSelect->addItem("DATA/VS07VS0.INT");
  ui->DirSelect->addItem("DATA/VS08VS0.INT");

  //DATAS
  ui->DirSelect->addItem("DATAS/ST00SR0.INT");
  ui->DirSelect->addItem("DATAS/ST01SR0.INT");
  ui->DirSelect->addItem("DATAS/ST01SR1.INT");
  ui->DirSelect->addItem("DATAS/ST02SR0.INT");
  ui->DirSelect->addItem("DATAS/ST02SR1.INT");
  ui->DirSelect->addItem("DATAS/ST03SR0.INT");
  ui->DirSelect->addItem("DATAS/ST03SR1.INT");
  ui->DirSelect->addItem("DATAS/ST04SR0.INT");
  ui->DirSelect->addItem("DATAS/ST04SR1.INT");
  ui->DirSelect->addItem("DATAS/ST05SR0.INT");
  ui->DirSelect->addItem("DATAS/ST05SR1.INT");
  ui->DirSelect->addItem("DATAS/ST06SR0.INT");
  ui->DirSelect->addItem("DATAS/ST06SR1.INT");
  ui->DirSelect->addItem("DATAS/ST07SR0.INT");
  ui->DirSelect->addItem("DATAS/ST07SR1.INT");
  ui->DirSelect->addItem("DATAS/ST08SR0.INT");
  ui->DirSelect->addItem("DATAS/ST09SR1.INT");

  //EXT
  ui->DirSelect->addItem("EXT/EXT00.WP2");
  ui->DirSelect->addItem("EXT/EXT01.WP2");
  ui->DirSelect->addItem("EXT/EXT02.WP2");
  ui->DirSelect->addItem("EXT/EXT03.WP2");
  ui->DirSelect->addItem("EXT/EXT04.WP2");
  ui->DirSelect->addItem("EXT/EXT05.WP2");
  ui->DirSelect->addItem("EXT/EXT06.WP2");
  ui->DirSelect->addItem("EXT/EXT07.WP2");
  ui->DirSelect->addItem("EXT/EXT08.WP2");
  ui->DirSelect->addItem("EXT/EXT09.WP2");
  ui->DirSelect->addItem("EXT/TITLE.WP2");

  //IRX
  ui->DirSelect->addItem("IRX/IOPRP242.IMG");
  ui->DirSelect->addItem("IRX/LIBSD.IRX");
  ui->DirSelect->addItem("IRX/MCMAN.IRX");
  ui->DirSelect->addItem("IRX/MCSERV.IRX");
  ui->DirSelect->addItem("IRX/MODHSYN.IRX");
  ui->DirSelect->addItem("IRX/MODMIDI.IRX");
  ui->DirSelect->addItem("IRX/MODMSIN.IRX");
  ui->DirSelect->addItem("IRX/PADMAN.IRX");
  ui->DirSelect->addItem("IRX/SDRDRV.IRX");
  ui->DirSelect->addItem("IRX/SIO2MAN.IRX");
  ui->DirSelect->addItem("IRX/TAPCTRL.IRX");
  ui->DirSelect->addItem("IRX/WAVE2PS2.IRX");

  //MDL
  ui->DirSelect->addItem("MDL/STG00.OLM");
  ui->DirSelect->addItem("MDL/STG01.OLM");
  ui->DirSelect->addItem("MDL/STG02.OLM");
  ui->DirSelect->addItem("MDL/STG03.OLM");
  ui->DirSelect->addItem("MDL/STG04.OLM");
  ui->DirSelect->addItem("MDL/STG05.OLM");
  ui->DirSelect->addItem("MDL/STG06.OLM");
  ui->DirSelect->addItem("MDL/STG07.OLM");
  ui->DirSelect->addItem("MDL/STG08.OLM");
  ui->DirSelect->addItem("MDL/STG09.OLM");
  ui->DirSelect->addItem("MDL/STGBN.OLM");

  //PSS
  ui->DirSelect->addItem("PSS/P3V2_US.PSS");

  //SND
  ui->DirSelect->addItem("SND/ST01GM0C.WP2");
  ui->DirSelect->addItem("SND/ST01GM0G.WP2");
  ui->DirSelect->addItem("SND/ST01GM0N.WP2");
  ui->DirSelect->addItem("SND/ST02GM0C.WP2");
  ui->DirSelect->addItem("SND/ST02GM0G.WP2");
  ui->DirSelect->addItem("SND/ST02GM0N.WP2");
  ui->DirSelect->addItem("SND/ST03GM0C.WP2");
  ui->DirSelect->addItem("SND/ST03GM0G.WP2");
  ui->DirSelect->addItem("SND/ST03GM0N.WP2");
  ui->DirSelect->addItem("SND/ST04GM0C.WP2");
  ui->DirSelect->addItem("SND/ST04GM0G.WP2");
  ui->DirSelect->addItem("SND/ST04GM0N.WP2");
  ui->DirSelect->addItem("SND/ST05GM0C.WP2");
  ui->DirSelect->addItem("SND/ST05GM0G.WP2");
  ui->DirSelect->addItem("SND/ST05GM0N.WP2");
  ui->DirSelect->addItem("SND/ST06GM0C.WP2");
  ui->DirSelect->addItem("SND/ST06GM0G.WP2");
  ui->DirSelect->addItem("SND/ST06GM0N.WP2");
  ui->DirSelect->addItem("SND/ST07GM0C.WP2");
  ui->DirSelect->addItem("SND/ST07GM0G.WP2");
  ui->DirSelect->addItem("SND/ST07GM0N.WP2");
  ui->DirSelect->addItem("SND/ST08GM0C.WP2");
  ui->DirSelect->addItem("SND/ST08GM0G.WP2");
  ui->DirSelect->addItem("SND/ST08GM0N.WP2");
  ui->DirSelect->addItem("SND/STBN0.WP2");
  ui->DirSelect->addItem("SND/STBN1.WP2");

  //VS
  ui->DirSelect->addItem("VS/VS01VS0.WP2");
  ui->DirSelect->addItem("VS/VS01VS1.WP2");
  ui->DirSelect->addItem("VS/VS01VS2.WP2");
  ui->DirSelect->addItem("VS/VS02VS0.WP2");
  ui->DirSelect->addItem("VS/VS02VS1.WP2");
  ui->DirSelect->addItem("VS/VS02VS2.WP2");
  ui->DirSelect->addItem("VS/VS03VS0.WP2");
  ui->DirSelect->addItem("VS/VS03VS1.WP2");
  ui->DirSelect->addItem("VS/VS03VS2.WP2");
  ui->DirSelect->addItem("VS/VS04VS0.WP2");
  ui->DirSelect->addItem("VS/VS04VS1.WP2");
  ui->DirSelect->addItem("VS/VS04VS2.WP2");
  ui->DirSelect->addItem("VS/VS05VS0.WP2");
  ui->DirSelect->addItem("VS/VS05VS1.WP2");
  ui->DirSelect->addItem("VS/VS05VS2.WP2");
  ui->DirSelect->addItem("VS/VS06VS0.WP2");
  ui->DirSelect->addItem("VS/VS06VS1.WP2");
  ui->DirSelect->addItem("VS/VS06VS2.WP2");
  ui->DirSelect->addItem("VS/VS07VS0.WP2");
  ui->DirSelect->addItem("VS/VS07VS1.WP2");
  ui->DirSelect->addItem("VS/VS07VS2.WP2");
  ui->DirSelect->addItem("VS/VS08VS0.WP2");
  ui->DirSelect->addItem("VS/VS08VS1.WP2");
  ui->DirSelect->addItem("VS/VS08VS2.WP2");

  //XTR
  ui->DirSelect->addItem("XTR/ST00SR0.XTR");
  ui->DirSelect->addItem("XTR/ST01SR0.XTR");
  ui->DirSelect->addItem("XTR/ST01SR1.XTR");
  ui->DirSelect->addItem("XTR/ST02SR0.XTR");
  ui->DirSelect->addItem("XTR/ST02SR1.XTR");
  ui->DirSelect->addItem("XTR/ST03SR0.XTR");
  ui->DirSelect->addItem("XTR/ST03SR1.XTR");
  ui->DirSelect->addItem("XTR/ST04SR0.XTR");
  ui->DirSelect->addItem("XTR/ST04SR1.XTR");
  ui->DirSelect->addItem("XTR/ST05SR0.XTR");
  ui->DirSelect->addItem("XTR/ST05SR1.XTR");
  ui->DirSelect->addItem("XTR/ST06SR0.XTR");
  ui->DirSelect->addItem("XTR/ST06SR1.XTR");
  ui->DirSelect->addItem("XTR/ST07SR0.XTR");
  ui->DirSelect->addItem("XTR/ST07SR1.XTR");
  ui->DirSelect->addItem("XTR/ST08SR0.XTR");
  ui->DirSelect->addItem("XTR/ST09SR0.XTR");

  //ROOT
  ui->DirSelect->addItem("SCUS_971.67");
  ui->DirSelect->addItem("SYSTEM.CNF");

  //do i regret doing this?
  //yes, my eyes hurt
}
