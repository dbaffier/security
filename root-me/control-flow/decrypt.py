import angr
import claripy
import sys


def main():
    p = angr.Project('a.out')

    flag_chars = [claripy.BVS('flag_%d' % i, 8) for i in range(8)]
    flag = claripy.Concat(*flag_chars + [claripy.BVV(b'\n')])

    st = p.factory.full_init_state(
        args=['./a.out'],
        add_options=angr.options.unicorn,
        stdin=flag,
    )

    sm = p.factory.simulation_manager(st)
    sm.run()

    for pp in sm.deadended:
        output = state.posix.dumps(sys.stdout.fileno())
        print(output)


if __name__ == "__main__":
    main()
