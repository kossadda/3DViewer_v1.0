################################################################################
#     ____  _______      ___                                    __     ___     #
#    |___ \|  __ \ \    / (_)                                  /_ |   / _ \    #
#      __) | |  | \ \  / / _  _____      _____ _ __     __   __ | |  | | | |   #
#     |__ <| |  | |\ \/ / | |/ _ \ \ /\ / / _ \ '__|    \ \ / / | |  | | | |   #
#     ___) | |__| | \  /  | |  __/\ V  V /  __/ |  _____ \ V /  | | _| |_| |   #
#    |____/|_____/   \/   |_|\___| \_/\_/ \___|_| |_____| \_/   |_|(_)\___/    #
#                                                                              #
################################################################################


################################################################################
#                                 _       _     _                              #
#                                (_)     | |   | |                             #
#                __   ____ _ _ __ _  __ _| |__ | | ___  ___                    #
#                \ \ / / _` | '__| |/ _` | '_ \| |/ _ \/ __|                   #
#                 \ V / (_| | |  | | (_| | |_) | |  __/\__ \                   #
#                  \_/ \__,_|_|  |_|\__,_|_.__/|_|\___||___/                   #
#                                                                              #
################################################################################


#================================== COMPILER ==================================#
PROJECT_NAME = 3d_viewer
CC = gcc
#==============================================================================#


#=============================== DIRECTORY NAMES ==============================#
OBJ_DIR = ./obj
MODULES_DIR = ./modules
GUI_DIR = ./gui
TEST_DIR = ./tests
REPORT_DIR = ./report
DVI_DIR = ./../docs
DIST_DIR = ./../dist
BUILD = ./../bin
#==============================================================================#

#==================================== FLAGS ===================================#
# MAIN FLAGS FOR COMPILER
CFLAGS = -Wall -Wextra -pedantic -std=c11 -g
# CFLAGS = -Wall -Werror -Wextra -pedantic -std=c11

# CHECK LIBRARY FOR LINKING
LDFLAGS = -lcheck -lsubunit -lm

# FLAGS FOR COVERING MODULES
GCOV_FLAGS = -fprofile-arcs -ftest-coverage -lgcov $(LDFLAGS)

# FLAGS FOR VALGRING TEST
VAL = --tool=memcheck --leak-check=yes

# FLAGS FOR CPPCHECK TEST
CPPCHECK = --enable=all --suppress=missingIncludeSystem
#==============================================================================#


#================================ TARGET NAMES ================================#
LIBRARY = $(PROJECT_NAME).a
TARGET = test
GCOV = gcov_report
#==============================================================================#


#================================ MAIN HEADER =================================#
MAIN_H = $(shell find ./ -maxdepth 1 -name "*.h")
#==============================================================================#


#====================== LIST OF FILE AND DIRS IN MODULES ======================#
MODULES_DIRS = $(shell find $(MODULES_DIR) -type d)
MODULES_C = $(shell find $(MODULES_DIR) -type f -name "*.c")
MODULES_H = $(shell find $(MODULES_DIR) -type f -name "*.h")
MODULES_O = $(notdir $(MODULES_C:%.c=%.o))
MODULES_OBJ_PATH = $(addprefix $(OBJ_DIR)/, $(MODULES_O))
GUI_MODULES = $(shell find $(GUI_DIR) -type f -name "*.cpp")
GUI_HEADERS = $(shell find $(GUI_DIR) -type f -name "*.h")
#==============================================================================#


#==================== LIST OF FILE AND DIRS IN TEST MODULES ===================#
TEST_DIRS = $(shell find $(TEST_DIR) -type d)
TEST_C = $(shell find $(TEST_DIR) -type f -name "*.c")
TEST_H = $(shell find $(TEST_DIR) -type f -name "*.h")
TEST_O = $(notdir $(TEST_C:%.c=%.o))
TEST_OBJ_PATH = $(addprefix $(OBJ_DIR)/, $(TEST_O))
#==============================================================================#


#================= LIST OF FILES TO CLANG-FORMAT AND CPPCHECK =================#
C_FILES = $(MODULES_C) $(TEST_C)
H_FILES = $(MODULES_H) $(MAIN_H) $(TEST_H)
ALL_FILES = $(C_FILES) $(GUI_MODULES) $(H_FILES)
#==============================================================================#


#=============== CONFIGURING PATH TO SEARH FOR UNPREFIXED PATHS ===============#
vpath %.c $(MODULES_DIRS) : $(GUI_DIRS) : $(TEST_DIRS)
vpath %.o $(OBJ_DIR)
#==============================================================================#


################################################################################
#                      _                       _                               #
#                     | |                     | |                              #
#                    _| |_ __ _ _ __ __ _  ___| |_ ___                         #
#                   |_  __/ _` | '__/ _` |/ _ \ __/ __|                        #
#                     | || (_| | | | (_| |  __/ |_\__ \                        #
#                      \__\__,_|_|  \__, |\___|\__|___/                        #
#                                    __/ |                                     #
#                                   |___/                                      #
################################################################################

#================================= MAIN TARGETS ===============================#

.PHONY: $(LIBRARY) $(TARGET) $(GCOV)

all: install run

install: $(LIBRARY)
	@mkdir -p $(BUILD)
	cd $(BUILD) && cmake ./../src && make	

uninstall: clean
	rm -rf $(BUILD)

$(LIBRARY): $(OBJ_DIR) $(MODULES_O) $(MODULES_H) $(MAIN_H)
	@ar rcs $@ $(MODULES_OBJ_PATH)
	@ranlib $@

$(TARGET): $(LIBRARY) $(TEST_O)
	@$(CC) $(TEST_OBJ_PATH) $(LIBRARY) $(LDFLAGS) -o $@
	@-./$@

$(GCOV): $(REPORT_DIR) $(LIBRARY) $(TEST_O)
	$(CC) $(TEST_OBJ_PATH) $(MODULES_C) $(GCOV_FLAGS) -o $(addprefix $(OBJ_DIR)/, $(TARGET))
	./$(addprefix $(OBJ_DIR)/, $(TARGET))
	gcovr -r . --html --html-details -o $(REPORT_DIR)/coverage.html
	xdg-open $(REPORT_DIR)/coverage.html

dvi:
	rm -rf $(DVI_DIR)
	doxygen Doxyfile
	xdg-open $(DVI_DIR)/html/index.html

dist: uninstall
	@rm -rf $(DIST_DIR)
	@echo "Creating a distribution..."
	@mkdir -p $(DIST_DIR)/$(PROJECT_NAME)
	@cp -r ./ $(DIST_DIR)/$(PROJECT_NAME) && rm -rf $(DIST_DIR)/$(PROJECT_NAME)/tests
	@echo "Distribution packaging..."
	@tar -czf $(DIST_DIR)/$(PROJECT_NAME).tar.gz -C $(DIST_DIR) $(PROJECT_NAME)
	@echo "\033[33mDistribution created: $(DIST_DIR)/$(PROJECT_NAME).tar.gz\033[0m"
	@rm -rf $(DIST_DIR)/$(PROJECT_NAME)

clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(REPORT_DIR)
	rm -rf $(DVI_DIR)
	rm -rf $(DIST_DIR)
	rm -rf $(GCOV)
	rm -rf ../build*
	rm -rf build*
	rm -rf ~/.config/3DViewer
	rm -f $(TARGET)
	rm -f $(GUI_DIR)/*.o $(GUI_DIR)/Makefile $(GUI_DIR)/moc* $(GUI_DIR)/qrc* $(GUI_DIR)/ui_* $(GUI_DIR)/.qmake*
	rm -f ./CMake*.user
	rm -f *.a *.o 
	rm -f *.gc*
	rm -f main

rebuild: uninstall install
#==============================================================================#


#============================== CREATE DIRECTORIES ============================#
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(REPORT_DIR):
	@mkdir -p $(REPORT_DIR)
#==============================================================================#


#============================== OBJECTIVE TARGETS =============================#
%.o: %.c $(MODULES_H)
	@$(CC) $(CFLAGS) -c -o $(addprefix $(OBJ_DIR)/, $@) $<

%_test.o: %_test.c
	@$(CC) $(CFLAGS) -c -o $(addprefix $(OBJ_DIR)/, $@) $<
#==============================================================================#


#=============================== CHECKS TARGETS ===============================#
clang_check:
	clang-format -style=Google -n $(ALL_FILES)

cppcheck:
	$@ $(CPPCHECK) $(MODULES_C) $(MODULES_H)

valgrind: $(TARGET)
	@printf '\033[1;33m\n\t\t\t\t                   _            _           _   _            _   _             \n'
	@printf '\t\t\t\t                  | |          (_)         | | | |          | | (_)            \n'
	@printf '\t\t\t\t       __   ____ _| | __ _ _ __ _ _ __   __| | | |_ ___  ___| |_ _ _ __   __ _ \n'
	@printf '\t\t\t\t       \ \ / / _` | |/ _` | '\''__| | '\''_ \ / _` | | __/ _ \/ __| __| | '\''_ \ / _` |\n'
	@printf '\t\t\t\t        \ V / (_| | | (_| | |  | | | | | (_| | | ||  __/\__ \ |_| | | | | (_| |\n'
	@printf '\t\t\t\t         \_/ \__,_|_|\__, |_|  |_|_| |_|\__,_|  \__\___||___/\__|_|_| |_|\__, |\n'
	@printf '\t\t\t\t                      __/ |                                               __/ |\n'
	@printf '\t\t\t\t                     |___/                                               |___/ \n\033[0m\n'

	@$@ $(VAL) ./$(TARGET) > val.txt 2>&1 && \
	{ \
		printf "\033[1;33m\n"; \
		printf "###########################################################################################################################################################\n\n"; \
		printf "                                                                 Valgrind test results:\n"; \
		printf "                                                                Passed tests $$(grep "ERROR SUMMARY: 0" -c val.txt) from $$(grep "ERROR SUMMARY:" -c val.txt)\n\n"; \
		printf "###########################################################################################################################################################\n"; \
		printf "\033[0m\n"; \
	}
#==============================================================================#


#============================= ADDITIONAL TARGETS =============================#
run:
	@./$(BUILD)/$(PROJECT_NAME)

debug:
	@$(CC) $(CFLAGS) debug.c $(MODULES_C) -lm -o main
	@./main

clang_fix:
	clang-format -style=Google -i $(ALL_FILES)

docker_build:
	docker build -t $(PROJECT_NAME) .
	-docker run -d --name $(PROJECT_NAME) $(PROJECT_NAME)
	-docker cp $(PROJECT_NAME):/$(PROJECT_NAME)/bin ./..
	-docker stop $(PROJECT_NAME)
	-docker rm -f $(PROJECT_NAME)
	-docker rmi -f $(PROJECT_NAME):latest

qmake_build: $(LIBRARY)
	cd $(GUI_DIR) && qmake && make
	rm -rf $(BUILD)
	mkdir $(BUILD)
	mv $(GUI_DIR)/$(PROJECT_NAME) $(BUILD)

dependencies:
	sudo apt install cppcheck
	sudo apt install clang-format
	sudo apt-get install check
	sudo apt install doxygen
	sudo apt-get install graphviz
	sudo apt install cmake
	sudo apt install qtbase5-dev
	sudo apt install libqt5opengl5-dev
#==============================================================================#
