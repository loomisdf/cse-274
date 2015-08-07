
class Bicycle{
	public:
		Bicycle();
		Bicycle(int);
		virtual ~Bicycle();
		int getSpeed();
		void applyBrake(int);
		void speedUp(int);

	private:
		int speed;
};