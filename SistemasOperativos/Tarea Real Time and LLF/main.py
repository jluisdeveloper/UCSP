import os
from functools import reduce
from typing import List, Optional
import builtins
import matplotlib.pyplot as plt

tag: Optional[str] = None


def change_print_tag(_tag: str):
    global tag
    if _tag:
        os.remove(f"output/{_tag}.txt")
    tag = _tag


def print(msg: str, *args):
    if args:
        msg = msg + " ".join(args)
    builtins.print(msg)
    if tag:
        builtins.print(f"[{tag}] {msg}")
        with open(f"output/{tag}.txt", "a+") as f:
            f.write(msg + "\n")


def lcm(x, y):
    if x > y:
        greater = x
    else:
        greater = y

    while True:
        if (greater % x == 0) and (greater % y == 0):
            lcm_val = greater
            break
        greater += 1

    return lcm_val


def array_lcm(a: List):
    return reduce(lcm, a)


class Task:
    name: str
    color: str
    arrival_time: float
    period: float
    exec_time: float
    deadline: float

    consumed_time: float
    time_to_deadline: float
    time_to_release: float

    def __init__(self,
                 name: str,
                 color: str,
                 t1: float,
                 t2: float,
                 at: float):
        self.name = name
        self.color = color
        self.arrival_time = at
        self.period = t1
        self.exec_time = t2
        self.deadline = t1

        self.consumed_time = 0
        self.time_to_deadline = self.deadline + self.arrival_time
        self.time_to_release = self.arrival_time

    def is_ready(self,
                 current_timeframe: float, ):
        return self.arrival_time > current_timeframe

    def compute_slack_time(self,
                           current_timeframe: float,
                           executed_time: int = 0) -> float:
        remaining_exec_time = self.exec_time - executed_time
        return self.deadline - current_timeframe - remaining_exec_time

    def __repr__(self):
        return f"{self.name}({self.period}, {self.exec_time}), consumed:{self.consumed_time} ttd:{self.time_to_deadline}"


class Execution:
    task: Task
    start: float
    end: float

    @property
    def exec_time(self):
        return self.end - self.start;

    def __init__(self, task: Task, start: float, end: float):
        self.task = task
        self.start = start
        self.end = end

    def __repr__(self):
        return f"{self.task.name}: {self.start} -> {self.end}"


class Executions:
    executions: List[Execution] = []

    def append(self, t: Task, time: float, exec_time: float):
        if len(self.executions) == 0:
            self.executions.append(Execution(t, time, time + exec_time))
            return

        last_exec = self.executions[-1]
        if last_exec.task == t and last_exec.end == time:
            last_exec.end = time + exec_time
            return

        self.executions.append(Execution(t, time, time + exec_time))

    def __repr__(self):
        return repr(self.executions)


class LeastLaxityFirstScheduler:
    time_step: float
    tasks: List[Task] = []
    current_time: float = 0

    def __init__(self, tasks: List[Task], time_step: float):
        self.tasks = tasks
        self.time_step = time_step

        self.next_tick(prime_run=True)
        self.current_time = 0

    def next_tick(self, /, prime_run=False):
        if not prime_run:
            self.current_time += self.time_step
        else:
            self.current_time = 0

        for t in self.tasks:
            if not prime_run and t.time_to_deadline > 0:
                t.time_to_deadline -= self.time_step
            elif not prime_run and t.consumed_time != t.exec_time:
                raise Exception(f"{t.name} Se perdio el deadline")

            if t.time_to_release > 0:
                t.time_to_release -= self.time_step
            else:
                t.consumed_time = 0
                t.time_to_release = t.period
                t.time_to_deadline = t.deadline

    def compute_hyperperiod(self) -> float:
        return array_lcm([t.period for t in self.tasks])

    def is_task_schedulable(self, task: Task):
        return self.current_time >= task.arrival_time and \
               task.consumed_time < task.exec_time

    def laxity(self, t: Task):
        return t.time_to_deadline - (t.exec_time - t.consumed_time)

    def get_best_task(self) -> Optional[Task]:
        laxity_of_schedulable_tasks = [(self.laxity(t), t) for t in self.tasks if self.is_task_schedulable(t)]
        if len(laxity_of_schedulable_tasks) == 0:
            print("laxity: Vacio")
            return None
        print("laxity:", " ".join(map(lambda x: f"{x[1].name}:{x[0]}", laxity_of_schedulable_tasks)))
        min_laxity = min(laxity_of_schedulable_tasks, key=lambda x: x[0])
        print(f"min: {min_laxity[1].name}:{min_laxity[0]}")
        return min_laxity[1]

    def schedule(self, time: float = None) -> Executions:
        if time is None:
            time = self.compute_hyperperiod()

        self.executions = Executions()

        while self.current_time < time:
            best_task = self.get_best_task()
            if best_task is not None:
                best_task.consumed_time += self.time_step
                print(f"t=[{self.current_time}\t] -> {best_task.name}")
                self.executions.append(best_task, self.current_time, self.time_step)
            else:
                print(f"t=[{self.current_time}\t] -> NONE")
            self.next_tick()

        return self.executions


def plot_executions(executions: List[Execution]):
    periods_colors = [e.task.color for e in executions]
    periods = [(e.start, e.exec_time) for e in executions]

    fig, ax = plt.subplots()
    tasks = list({e.task for e in executions})
    tasks.sort(key=lambda x: x.name, reverse=True)
    ax.broken_barh(periods,
                   (1, 5),
                   facecolors=periods_colors)
    ax.set_ylim(0, 30)
    ax.set_xlim(executions[0].start, executions[-1].end)
    ax.spines['right'].set_visible(False)
    ax.spines['left'].set_visible(False)
    ax.spines['top'].set_visible(False)
    ax.axes.yaxis.set_visible(False)

    ax.set_xlabel(f'Ejecucion en el Timeline')
    fig.suptitle(f'Least Laxity First',
                 fontsize=15)

    ticks = [e.start for e in executions]
    ticks += [e.end for e in executions if e not in ticks]
    ax.set_xticks(ticks)
    plt.xticks(rotation=-90)
    plt.tight_layout()

    for i, t in enumerate(tasks):
        fig.patches.extend([plt.Rectangle((0.04, 0.35 + (i * 0.12)), 0.24, 0.1,
                                          fill=True, color=t.color, zorder=1000,
                                          transform=fig.transFigure, figure=fig)])
        fig.text(0.3, 0.38 + (i * 0.12), f"{t.name}({t.arrival_time}, {t.period}, {t.exec_time}, {t.deadline})",
                 fontsize=20)


def schedule_and_plot(scheduler, time: float = None):
    tag = f"Timeline-{'hyperperiod' if time is None else time}"
    change_print_tag(tag)
    executions = scheduler.schedule(time)
    plot_executions(executions.executions)
    plt.savefig("output/"+tag + ".png")


def main():
    print("Nombre: Jorge Huanca Mamani")

    tasks = [
        Task("A1", "tab:red", 20, 10, 0),
        Task("A2", "orange", 40, 10, 20),
        Task("B1", "tab:blue", 50, 10, 0),
        Task("B2", "tab:pink", 100, 10, 50),
        Task("C1", "tab:grey", 50, 15, 0),
        Task("C2", "tab:green", 100, 15, 50),
    ]

    scheduler = LeastLaxityFirstScheduler(tasks, time_step=5)

    schedule_and_plot(scheduler, 100)

if __name__ == "__main__":
    main()