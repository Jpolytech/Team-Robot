int main()
{

    // Option 1:

    Timer1 timer = Timer1(WaveformGenerationMode::CTC, ClockSelect::PRESCALER_8);

    timer.startTimer(1000);

    timer.stopTimer();

    // Option 2:
    Timer1 timer = Timer();

    timer.startTimer(WaveformGenerationMode::CTC, ClockSelect::PRESCALER_8);

    timer.stopTimer();

    timer.startTimer(WaveformGenerationMode::Normal, ClockSelect::PRESCALER_16);
}