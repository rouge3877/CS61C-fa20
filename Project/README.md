# CS61C - projects

This subrepository contains the projects of CS61C, only the *Finished* projects and *Ongoing* projects will be contained in this subrepository.

## [Proj#1](https://inst.eecs.berkeley.edu/~cs61c/fa20/projects/proj1/) Game of Life

### Description
I used nearly 4 hours to finish this Project. Overall, this Proj is not hard.
But is pity that i do not implement the [Multiple Colors](https://inst.eecs.berkeley.edu/~cs61c/fa20/projects/proj1/#multiple-colors) mode. But in fact, is easy to complement. 
1. Let the `getState()` to return a `uint8_t`from $0 \to 255$ to show different states, replace the 0/1 return currently.
	// assign the next state

2. In `evaluateOneCell()`, Rewrite Transition state function which is `uint8_t next_state = ((rule >> (9 * _dead_0_or_live_1_ + alive_neighbors)) & _1_bit);` now. And assign different color with different state

*In addition:* Because of unknown problem, I can not run `frames.csh` in `bash` or `zsh` even though I replace the `.csh` to `.zsh/.sh` in file name and change the first line in the file. So if you want to try 

### Usage

*Is no doubt that you should `cd Game-of-Life` at first* :D

After `make gameoflife`to compile, you can run ./frames.csh as follows :
```bash
./frames.csh <imagename> <rule> <frames>
```

*(If it fails due to permission denied, try running the command: `chmod +x frames.csh`)*

This script will use the image and the game rule you supply to create requested number of frames.

For example, to create the gif above, you can just run :

```bash
./frames.csh xkcd 0x1808 100
```

The frames will be outputted in `studentOutputs/[prefix]`. To regenerate frames, you will need to delete the folder of previously generated images. 
