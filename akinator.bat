g++ -g -DTREE_USE_CHAR -DTREE_DEBUG cpp_files\main.cpp cpp_files\main_functions.cpp cpp_files\get_tree.cpp cpp_files\guess_mode.cpp cpp_files\dump.cpp -Ih_files -o akinator.exe ^
-finput-charset=UTF-8 -fexec-charset=UTF-8 -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wfloat-equal -Winline -Wunreachable-code ^
-Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe ^
-fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers ^
-Wlogical-op -Wno-missing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo ^
-Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -Werror=vla -D_DEBUG ^
-D_EJUDGE_CLIENT_SIDE
.\akinator.exe database.txt
