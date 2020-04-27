class Window;

class Emulator
{
	public:
		Emulator(const char* filename);
		~Emulator();
		void run();
		void update();
		void render();

	private:
		Window* window = nullptr;
};
