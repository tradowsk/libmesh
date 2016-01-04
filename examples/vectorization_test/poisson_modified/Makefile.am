example_name  = poisson_modified
check_SCRIPTS = run.sh
install_dir   = $(examples_install_path)/vectorization_test/poisson_modified
data          = poisson_modified.C exact_solution.C fe_shape_function.h run.sh
sources       = $(data) run.sh

CLEANFILES = out.pvtu

clean-local:
	-rm -rf out_*.vtu

##############################################
# include common example environment
include $(top_srcdir)/examples/Make.common
