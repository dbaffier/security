import angr

START = 0x400B30  # start of main
FIND = 0x403A40  # part of program that prints the flag
# all addresses after a failed check occur on a fixed interval
AVOID = [0x403A7E + i * 60 for i in range(100)]

BUF_LEN = 100


def char(state, c):
    '''returns constraints s.t. c is printable'''
    return state.se.And(c <= '~', c >= ' ')


def main():
    p = angr.Project('FUck_binary')

    print('creating state')
    state = p.factory.blank_state(addr=START)

    print('adding constaints to stdin')
    for i in range(BUF_LEN):
        c = state.posix.files[0].read_from(1)
        state.se.add(char(state, c))

    # even though we mark stdin as 100 long angr can still chose to cut it off
    state.posix.files[0].seek(0)
    state.posix.files[0].length = 100

    print('creating path and explorer')
    path = p.factory.path(state)
    ex = p.surveyors.Explorer(start=path, find=FIND, avoid=AVOID)

    print('running explorer')
    ex.run()

    print('found solution')
    correct_input = ex._f.state.posix.dumps(
        0)  # ex._f is equiv. to ex.found[0]

    # we didn't know how long the input had to be except < 100 bytes
    team_name = correct_input[:correct_input.index('\x00')]

    print('found correct input/team name: {}'.format(repr(team_name)))

    return team_name


def test():
    assert main(
    ) == '@@@(h@@@@f@v@ @@/@vCo@&D@ACHP@@@@@@@@D@@ @X@@@@@B@h@]@@@W@UB@"(@Lq@@@@@,FBtH@?6@@" * k[Q@@@@@@@@@I@@'


if __name__ == '__main__':
    main()
