#pragma once

//System includes
#include <string>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <thread>
#include <chrono>

//cube-lib includes
#include "cube-lib/cube-encrypter.h"
#include "cube-lib/cube-ini-parser.h"
#include "cube-lib/cube-database.h"

//Qt includes
#include <QDialog>
#include <QMainWindow>
#include <QListWidgetItem>
#include <QMessageBox>
#include <QDesktopServices>
#include <QUrl>
#include <QFileDialog>
#include <QDateTime>

//Global declares
extern std::string SETTINGS_FILE;
extern std::string DATABASE_FILE;
#define VERSION "3.0.0"
