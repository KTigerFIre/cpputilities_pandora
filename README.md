# Pandora
Pandora will be a C++ library that provides various utilities for software development. 
It includes the following components:
* StopWatch
* TimeLogger

## Usage
### 'StopWatch': A simple stopwatch class for measuring elapsed time.
```c++
#include <stop_watch.h>

int main()
{
    pandora::StopWatch stopwatch;
    stopwatch.Start();
    // some code to be timed...
    double elapsed_time = stopwatch.Stop();
    std::cout << "Elapsed time: " << elapsed_time << " seconds" << std::endl;
    return 0;
}
```
### 'LapLogger': A lap time check class for measuring the elapsed time of each code line and store the results. 
```c++
#include <iostream>
#include <thread>
#include "lap_logger.h"

int main()
{
    std::cout << "Hello World!\n";

    pandora::LapLogger lap_logger(true);
    std::cout << "Time logger start " << std::endl;
    lap_logger.Start();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    lap_logger("step1");
    std::this_thread::sleep_for(std::chrono::seconds(1));
    lap_logger("step2");

    std::this_thread::sleep_for(std::chrono::seconds(1));
    lap_logger("step3");
    std::this_thread::sleep_for(std::chrono::seconds(2));
    lap_logger("step4");

    std::cout << lap_logger.ShowResult(pandora::LapLogger::LAP_LOGGER_SECOND) <<  std::endl;

    return 0;
}
```


## Contributing
Contributions to Pandora are welcome! If you have an idea for a new feature, or if you find a bug, please open an issue or submit a pull request on the GitHub repository.

## License
Pandora is licensed under the MIT License. See the LICENSE file for details.
