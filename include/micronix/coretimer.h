#ifndef MICRONIX_CORETIMER_H
#define MICRONIX_CORETIMER_H

struct coretimer_driver{
  int (*probe)(struct platform_data*);
  /* Get the current count of the timer */
  int (*get_count)(void);
  /* Set the current count of the timer */
  void (*set_count)(int);
  /* Set how many cycles for the next interrupt */
  void (*set_cycles)(int);
};

#endif
