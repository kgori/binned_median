binned_median
=============

Intended to calculate median depths of BAM files, with low memory requirements.
Takes a stream of depths at each position (e.g. from samtools depth -a), and
increments a bin-count for each integer depth (up to 1000000-1; the final bin
is used to keep count of depth >= 1000000).

Usage:

    # Stream the depth info into the program
    samtools depth -a BAM | cut -f3 | binned_median


Build instructions:

    git clone https://github.com/kgori/binned_median.git
    cd binned_median
    cmake -B build_folder -S .
    cmake --build build_folder
    cmake --install build_folder [--prefix install_folder]

