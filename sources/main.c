/*
 * main.c
 *
 * Licensed under MIT license
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#include "universe.h"
#include "args.h"
#include "text.h"
#include "util.h"

int main(int argc, char **argv)
{
  args_t args;         /* Program arguments (from argv) */
  universe_t universe; /* The universe itself (wow) */
  double potential;    /* The universe's potential energy */

  /* We don't need a perfectly random generator */
  srand((unsigned int)time(NULL));

  /* That's the welcome message */
  puts(TEXT_START);

  /* Parse the arguments */
  args_init(&args);
  if (args_parse(&args, argc, argv) == NULL)
    return (retstri(EXIT_FAILURE, TEXT_MAIN_FAILURE, __FILE__, __LINE__));

  /* Initialise the universe with the arguments */
  if (universe_init(&universe, &args) == NULL)
    return (retstri(EXIT_FAILURE, TEXT_MAIN_FAILURE, __FILE__, __LINE__));

  /* Reduce the potential energy before simulating */
   if (universe_reducepot(&universe, &args) == NULL)
    return (retstri(EXIT_FAILURE, TEXT_MAIN_FAILURE, __FILE__, __LINE__));

  /* Compute the potential energy */
   if (universe_energy_potential(&universe, &potential) == NULL)
     return (retstri(EXIT_FAILURE, TEXT_MAIN_FAILURE, __FILE__, __LINE__));

  /* Print some useful information */
  puts(TEXT_INFO_REFERENCE);
  printf(TEXT_INFO_PATH, args.path);
  printf(TEXT_INFO_NAME, universe.meta_name);
  printf(TEXT_INFO_AUTHOR, universe.meta_author);
  printf(TEXT_INFO_COMMENT, universe.meta_comment);
  printf(TEXT_INFO_REF_ATOM_NB, universe.ref_atom_nb);
  printf(TEXT_INFO_REF_BOND_NB, universe.ref_bond_nb);
  printf("\n");
  puts(TEXT_INFO_SIMULATION);
  printf(TEXT_INFO_SYS_COPIES, universe.copy_nb);
  printf(TEXT_INFO_ATOMS, universe.atom_nb);
  printf(TEXT_INFO_TEMPERATURE, universe.temperature);
  printf(TEXT_INFO_PRESSURE, args.pressure/1E2);
  printf(TEXT_INFO_DENSITY, args.density/1E3);
  printf(TEXT_INFO_POTENTIAL_ENERGY, potential*1E12);
  printf(TEXT_INFO_UNIVERSE_SIZE, universe.size*1E12);
  printf(TEXT_INFO_SIMULATION_TIME, args.max_time*1E9);
  printf(TEXT_INFO_TIMESTEP, args.timestep*1E15);
  printf(TEXT_INFO_FRAMESKIP, args.frameskip);
  printf(TEXT_INFO_ITERATIONS, (long)ceil(args.max_time/args.timestep));

  /* Let's roll */
  return (universe_simulate(&universe, &args));
}
