/*#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <stdio.h>
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <GLFW/glfw3.h>*/
#include <iostream>

#include "sudoku.h"
#include "backtrack_solution.h"
#include "backjump_leaf_solution.h"
#include "DLX.h"
#include "configuration_set.h"

void menu(DLX& DLX_solution, backjump_leaf_solution& BJ_solution, backtrack_solution& BT_solution, std::string clue, sudoku sudo, configuration_set config);
void set_clue(std::string& clue);
void solve(DLX& DLX_solution, backjump_leaf_solution& BJ_solution, backtrack_solution& BT_solution, std::string clue, configuration_set config);
void configure(configuration_set& config);
void load_anti_example(std::string& clue, sudoku& sudo);

int main(int argc, char** argv) {

	int flag;
	sudoku sudo("..1...9...9.1.4.6.5...9...7.7.2.3.8...2...5...4.6.5.1.8...2...1.6.7.8.9...9...8..");
	std::string clue = "..1...9...9.1.4.6.5...9...7.7.2.3.8...2...5...4.6.5.1.8...2...1.6.7.8.9...9...8..";
	DLX DLX_solution(sudo);
	backjump_leaf_solution BJ_solution(sudo);
	backtrack_solution BT_solution(sudo);
	configuration_set config;

	std::cout << "Sudoku solver: a triple method implementation." << std::endl;
	std::cout << "Solving sudoku in three easy steps!" << std::endl;
	std::cout << "1. Enter your sudoku clue with flag 2." << std::endl;
	std::cout << "2. Choose a mod with flag 3." << std::endl;
	std::cout << "3. Wait for the solved sudoku!" << std::endl;
	std::cout << "Extra configurations can be found with flag 5." << std::endl << std::endl;
	std::cout << "One default sudoku has been loaded." << std::endl;

	menu(DLX_solution, BJ_solution, BT_solution, clue, sudo, config);

}

void menu(DLX& DLX_solution, backjump_leaf_solution& BJ_solution, backtrack_solution& BT_solution, std::string clue, sudoku sudo, configuration_set config) {
	int flag = -1;
	while (flag != 0) {
		std::cout << std::endl;
		std::cout << "Operations:" << std::endl;
		std::cout << "1. Set sudoku clue." << std::endl;
		std::cout << "2. Solve sudoku." << std::endl;
		std::cout << "3. Load anti brute force sudoku example." << std::endl;
		std::cout << "4. Check current sudoku." << std::endl;
		std::cout << "5. Extra configurations." << std::endl;
		std::cout << "0. Quit :(" << std::endl;
		std::cout << "Please enter instructions (as a number):" << std::endl;
		std::cin >> flag;
		switch (flag) {
		case(1):
			std::cout << "Please enter a sudoku clue with \'.\' or \'0\' as the missing numbers." << std::endl;
			std::cout << "Example:" << std::endl;
			sudo.print_board();
			std::cout << std::endl;
			std::cout << "..1...9...9.1.4.6.5...9...7.7.2.3.8...2...5...4.6.5.1.8...2...1.6.7.8.9...9...8.." << std::endl;
			std::cout << "001000900090104060500090007070203080002000500040605010800020001060708090009000800" << std::endl;
			std::cin >> clue;
			set_clue(clue);
			break;
		case(2):
			solve(DLX_solution, BJ_solution, BT_solution, clue, config);
			break;
		case(3):
			load_anti_example(clue, sudo);
			break;
		case(4):
			sudo.set_clue(clue);
			sudo.print_board();
			break;
		case(5):
			configure(config);
			break;
		default:
			std::cout << "Wrong instruction! Please choose a valid option." << std::endl;
			break;
		}
	}
}

void set_clue(std::string& clue) {
	while (clue.size() != 81) {
		std::cout << "Wrong clue size! Please enter a valid clue with size 81." << std::endl;
		std::cin >> clue;
	}
	std::cout << "Done!" << std::endl;
}

void solve(DLX& DLX_solution, backjump_leaf_solution& BJ_solution, backtrack_solution& BT_solution, std::string clue, configuration_set config) {
	int flag = -1;
	std::cout << std::endl << "Sudoku solving" << std::endl;
	std::cout << "1. Solving the sudoku with backtracking. (Brute force)" << std::endl;
	std::cout << "2. Solving the sudoku with backjumping only at leaf dead ends. (Gaschnig's backjump)" << std::endl;
	std::cout << "3. Solving the sudoku with dancing links. (Donald Knuth's algorithm X)" << std::endl;
	std::cout << "0. Back to main menu.)" << std::endl;
	while (true) {
		std::cin >> flag;
		while (flag != 1 && flag != 2 && flag != 3 && flag != 0) {
			std::cout << "Wrong instruction! Please choose a valid option." << std::endl;
			std::cin >> flag;
		}
		if (flag == 0) {
			return;
		}
		if (flag == 1) {
			BT_solution.set_sudoku(sudoku(clue));
			BT_solution.solve(config);
		}
		if (flag == 2) {
			BJ_solution.set_sudoku(sudoku(clue));
			BJ_solution.solve(config);
		}
		if (flag == 3) {
			DLX_solution.set_sudoku(sudoku(clue));
			DLX_solution.solve(config);
		}
		std::cout << std::endl << "Solved!";
	}
}

void configure(configuration_set& config) {
	std::cout << std::endl << "Toggle configurations" << std::endl;
	std::cout << "1. Show time: Now ";
	if (config.show_time) {
		std::cout << "True." << std::endl;
	} else {
		std::cout << "False." << std::endl;
	}
	std::cout << "2. Show recursion times: Now ";
	if (config.show_recursion_count) {
		std::cout << "True." << std::endl;
	} else {
		std::cout << "False." << std::endl;
	}
	std::cout << "0. Back to main menu.)" << std::endl;
	int flag = -1;
	while (true) {
		std::cin >> flag;
		while (flag != 1 && flag != 2 && flag != 0) {
			std::cout << "Wrong instruction! Please choose a valid option." << std::endl;
			std::cin >> flag;
		}
		if (flag == 0) {
			return;
		}
		if (flag == 1) {
			config.show_time = !config.show_time;
		}
		if (flag == 2) {
			config.show_recursion_count = !config.show_recursion_count;
		}
		std::cout << std::endl << "Done!" << std::endl;
		std::cout << "Configuration now" << std::endl;
		std::cout << "1. Show time: Now ";
		if (config.show_time) {
			std::cout << "True." << std::endl;
		} else {
			std::cout << "False." << std::endl;
		}
		std::cout << "2. Show recursion times: Now ";
		if (config.show_recursion_count) {
			std::cout << "True." << std::endl;
		} else {
			std::cout << "False." << std::endl;
		}
	}
}

void load_anti_example(std::string& clue, sudoku& sudo) {
	clue = "..............3.85..1.2.......5.7.....4...1...9.......5......73..2.1........4...9";
	sudo.set_clue(clue);
	sudo.print_board();
	std::cout << "This sudoku is carefully designed to counter algorithms which use brute force to solve the sudoku." << std::endl;
	std::cout << "The most obivious feature is that the first row of the solved sudoku is 9 8 7 6 5 4 3 2 1." << std::endl;
	std::cout << "However, you might want to say what if we change the brute force program so that it first tries 9 or start from the other rows to avoid the first row." << std::endl;
	std::cout << "The fact is, this sudoku is carefully designed so that the first ten step to solve logically can only be done by candidate deduction and there is only one cell can be found to have only one candidate for each step." << std::endl;
	std::cout << "I believe this is the reason why it is so hard to solve the sudoku with backtracking algorithms." << std::endl;
	std::cout << "Be prepared to wait for about 1 minute for the first and second algorithm to solve the sudoku!" << std::endl;
	std::cout << "1. Hard version" << std::endl;
	std::cout << "2. Moderate version" << std::endl;
	std::cout << "3. Easy version" << std::endl;
	std::cout << "0. Back to main menu." << std::endl;
	int flag = -1;
	while (true) {
		std::cin >> flag;
		while (flag != 1 && flag != 2 && flag != 3 && flag != 0) {
			std::cout << "Wrong instruction! Please choose a valid option." << std::endl;
			std::cin >> flag;
		}
		if (flag == 0) {
			return;
		}
		std::cout << std::endl << "Done!" << std::endl;
		if (flag == 1) {
			clue = "..............3.85..1.2.......5.7.....4...1...9.......5......73..2.1........4...9";
			sudo.set_clue(clue);
			sudo.print_board();
		}
		if (flag == 2) {
			clue = "9.............3.85..1.2.......5.7.....4...1...9.......5......73..2.1........4...9";
			sudo.set_clue(clue);
			sudo.print_board();
		}
		if (flag == 3) {
			clue = "98............3.85..1.2.......5.7.....4...1...9.......5......73..2.1........4...9";
			sudo.set_clue(clue);
			sudo.print_board();
		}
	}
}

/*int main(int argc, char** argv) {
	if (!glfwInit())
		return -1;
	// Decide GL+GLSL versions
	// GL 3.0 + GLSL 130
	const char* glsl_version = "#version 130";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only

	GLFWwindow* window = glfwCreateWindow(3840, 2160, "project3demowindow", NULL, NULL);
	if (window == NULL)
		return 1;
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1); // Enable vsync

		// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.Fonts->AddFontFromFileTTF("Roboto-Medium.ttf", 50.0f);
	//(void)io; (what does this mean???????)
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsLight();

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);

	sudoku sudo;
	try {
		sudo.set_clue("987...........3.85..1.2.......5.7.....4...1...9.......5......73..2.1........4...9");
		//sudo.set_clue("..1...9...9.1.4.6.5...9...7.7.2.3.8...2...5...4.6.5.1.8...2...1.6.7.8.9...9...8..");
		//sudo.set_clue("..................123789456215436798.............................................");
		//sudo.set_clue("...26.7.168..7..9.19...45..82.1...4...46.29...5...3.28..93...74.4..5..367.3.18...");
		//sudo.set_clue("1..456789123456789123456789123456789123456789123456789123456789123456789123456789");
	} catch (const char* e) {
		std::cout << "Exception: " << e << std::endl;
	}

	backtrack_solution example(sudo);
	configuration_set config;
	config.show_time = true;
	config.show_recursion_count = true;
	Clock::time_point t0;
	Clock::time_point t1;
	t0 = Clock::now();
	example.solve(config);
	t1 = Clock::now();
	milliseconds ms = std::chrono::duration_cast<milliseconds>(t1 - t0);
	std::cout << ms.count() << "ms\n";
	backjump_leaf_solution example2(sudo);
	t0 = Clock::now();
	example2.solve(config);
	t1 = Clock::now();
	milliseconds ms2 = std::chrono::duration_cast<milliseconds>(t1 -t0);
	std::cout << ms2.count() << "ms\n";

	DLX dlx_example(sudo);
	t0 = Clock::now();
	dlx_example.solve(config);
	t1 = Clock::now();
	milliseconds ms3 = std::chrono::duration_cast<milliseconds>(t1 - t0);
	std::cout << ms3.count() << "ms\n";
	//dlx_example.~DLX();meibiyao

	bool show_my_first_window = true;
	bool show_demo_window = true;
	ImVec4 clear_color = ImVec4(0.3f, 0.6f, 0.9f, 1.00f);

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		if (show_demo_window)
			ImGui::ShowDemoWindow(&show_demo_window);
		{
			ImGui::Begin("my_first_window");
			ImGui::Text("This is some useful texttttttttt.");

			ImGui::End();
		}



		ImGui::Render();
		int display_w, display_h;
		glfwGetFramebufferSize(window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}*/