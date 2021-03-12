import angr
import claripy
import binascii

def main():
   length=8

   proj = angr.Project('./a.out')
   flag_chars = [claripy.BVS('flag_%i' % i, 8) for i in range(length)]
   flag = claripy.Concat( *flag_chars + [claripy.BVV(b'\n')]) # Add \n for scanf() to accept the input
   st = proj.factory.full_init_state( args='./a.out', stdin=flag, add_options=angr.options.unicorn )

   sm = proj.factory.simulation_manager(st)
   sm.run()

   y = []
   for x in sm.deadended:
      if b'OK!' in x.posix.dumps(1):
        print(x.posix.dumps(1))
        y.append(x)

   for s in y:
      flag = ''.join([hex(s.solver.eval(k))[2:] for k in flag_chars])
      print("Flag in hexa: %s" % flag)

if __name__ == '__main__':
    main()
