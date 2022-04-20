# Quanser 2 DOF Serial Flexible Link 

This is a repository with supporting material (texts, data, codes, ...) for the [Quanser 2DOF Serial Flexible Link](https://www.quanser.com/products/2-dof-serial-flexible-link/) apparatus. It is a simplified laboratory experimental model of a two-link serial robotic manipulator with flexible links.

![Quanser 2DOF Serial Flexible Link](figures/2-DOF-Serial-Flexible-Link-2-600x371.jpg)

## Control inputs and measured outputs

![Input output block diagram](figures/input_output_block_diagram.png)

### Control inputs (aka manipulated variables)

- The reference (required) values for the two electric currents through the two motors (in the two joints). Upper bound on the amplitude is 1 A (hardcoded in the Simulink models provided by Quanser is 0.94 A).

### Measured outputs

- The true values of the two electric currents.
- The two joint angles measured using encoders.
- The two strains measured using strain gauge sensors. 