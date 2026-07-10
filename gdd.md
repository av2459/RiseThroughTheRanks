# Rise Through The Ranks — Game Design Document

**Status:** Living document · v1.0 (complete first draft — all sections)
**Genre:** Open-world police career RPG (single-player)
**Platform (target):** PC first
**Team:** Solo / passion project · no fixed deadline · phased delivery
**Tone target:** Grounded procedural sim (realistic police work; authenticity is a pillar)
**Setting:** Penrose Bay — a fictional, modern-day, grounded mid-size American city on a real (NYPD-modelled) departmental skeleton
**Last updated:** 2026-07-10

> This is a living document. **All 15 sections now have a complete first draft (v1.0).**
> Each closes with an *Open Questions* list of decisions deliberately deferred; those are
> the live edges, consolidated in the master list at 15.C. The structure is the roadmap.

---

## 1. Vision Statement

*Rise Through The Ranks* is a single-player, open-world police RPG built on one
idea the genre's biggest games leave on the table: **your career is the story.**

You begin as a rookie who barely knows the law. Through the work itself — the
traffic stops, the calls, the investigations — you learn the job, build a record,
and choose who you become. Chase a promotion and specialize into vice, violent
crimes, or detective work, each carrying its own evolving story thread. Climb all
the way to Chief if you want to. Or don't: staying a beat cop for a hundred hours
is a legitimate way to play, not a failure to progress.

Where *Police Simulator: Patrol Officers* is a procedure sandbox with a static
identity, *The Precinct* is a fixed character in a fixed story, and GTA RP is
structureless emergent play, *Rise Through The Ranks* occupies the gap between
them: **authored career progression with player-chosen identity, inside a living
city — grounded in the real texture of police work.**

---

## 2. Design Pillars

These are the **five** non-negotiable truths of the player's experience. Every
feature, system, and cut decision gets checked against them. If a proposed feature
doesn't serve a pillar — or worse, undermines one — it doesn't ship.

### Pillar 1 — Your Career *Is* The Story
The narrative is not authored around a fixed protagonist and then handed to the
player. It emerges from, and wraps around, the player's own trajectory. Progression
is the plot. A player who spends three years in Vice and a player who sprints to
Chief should feel like they lived two genuinely different stories — because they
did. *Decision filter: does this feature make the player's own path feel more
authored and personal, or does it impose a story on top of it?*

### Pillar 2 — Every Rank Is A Destination, Not A Waypoint
The player decides how high to climb and where to specialize. Remaining a beat cop
forever must be as valid — and as fun — as becoming Chief. No rank is a "grind to
get past." This forces a hard discipline on us: every tier of play must be
intrinsically rewarding on its own, not just a gate in front of the next one.
*Decision filter: if a player chose to stay at this rank forever, would this
feature still make that a rich experience?*

### Pillar 3 — The Beat Must Be Fun Before The Ladder Is
The minute-to-minute loop — the stop, the call, the investigation — has to be
satisfying on its own merits, *before* any XP or rank reward is layered on top.
Progression is seasoning, not the meal. This is the pillar that protects us from
the genre's most common failure: a dull core loop disguised as compelling by a
stream of rewards. If we ever catch ourselves saying "it's boring but the unlocks
keep you going," we've broken this pillar. *Decision filter: strip out all
progression rewards — is the raw activity still fun?*

### Pillar 4 — A City That Remembers
The world is reactive and consequential. Your choices, your reputation, your arrest
record, and your mistakes persist and shape how the city and the department treat
you. This is what justifies building an open world at all: not size for its own
sake, but a living place that responds to a career unfolding inside it. A cop who
plays clean and a cop who cuts corners should live in visibly different cities.
*Decision filter: does this feature let the world respond to who the player has
become?*

### Pillar 5 — Grounded In The Real Work
The game takes real police work seriously. The fantasy is authenticity, not power —
procedure, judgment, evidence, and consequence are the point, not obstacles between
the player and an action-movie payoff. Getting it *right* is more satisfying than
getting it *loud*: reading a situation correctly, following the process, and
earning a clean result should feel better than a shootout. This is the pillar that
gives the other four their weight — a career only means something if the work it's
built on is real. It is also the pillar that most constrains us: when realism and
"cool" conflict, realism wins unless it makes the beat un-fun (see Pillar 3), and
that tension is resolved by *streamlining friction, never by faking the work*.
*Decision filter: does this feature deepen the authenticity of the job, or does it
trade the real texture of police work for spectacle?*

---

## 3. Production Principles (Solo-Dev Reality)

Design pillars describe the *player's* experience. These principles describe *how
one person actually ships this* without the open-world scope swallowing the project.
They are load-bearing — for a solo multi-year build, discipline here is the
difference between shipping and abandoning.

### 3.1 — Vertical Slice Before Horizontal Expansion
The single biggest killer of ambitious solo projects isn't attempting too much;
it's attempting it in the wrong *order* — building the whole city first and running
out of will before anything is fun. We invert that. **Phase 1 builds one district,
one specialization, and the complete rookie-to-first-promotion loop, genuinely fun
end to end.** Only once that vertical slice proves the core works do we expand
horizontally into the full city and the other specializations. Every roadmap
milestone (Section 13) obeys this.

### 3.2 — Systemic Bulk, Authored Beats
We do **not** hand-write six full branching campaigns — that scope is what turns
"parallel storylines" into a project-ending trap. Instead: the *bulk* of case and
incident content is generated systemically (procedural cases with narrative
flavor), and we hand-author only the **key rank-up beats and specialization
milestones**. This is how "a storyline that follows you" becomes achievable for
one person. (Detailed in Section 9.)

### 3.3 — Buy/Borrow The Solved Problems
Traffic, pathfinding, crowds, and world streaming are largely *solved* off the
shelf (e.g. engine-native crowd/traffic systems and sample city projects). We do
not reinvent these. Solo-dev time is spent on what makes *this* game unique — the
career and specialization systems — not on rebuilding a driving model from scratch.

### 3.4 — Fun Is Found, Not Planned
No amount of design doc replaces playtesting. Every system ships to a playable
state early and gets tuned by feel. The GDD is a compass, not a contract.

---

## 4. Core Gameplay Loop

> **Why this section comes first.** Pillar 3 says nothing else earns attention until
> the moment-to-moment is proven fun. This section defines what the player *does*
> with their hands and attention, second to second, at each career stage — before
> any XP, rank, or story reward is layered on. If the activity described here isn't
> fun with all rewards stripped out, the design has failed and we fix it here.

### 4.0 — The Loop In One Sentence
**Observe a situation, judge what it actually is, apply the correct procedure under
pressure, and live with the result** — repeated at escalating scope as the player's
rank grows, from a single traffic stop to running a department.

The verbs never really change; the *scope* of the judgment does. A rookie judges
"is this driver drunk or tired?" A detective judges "does this evidence support a
charge?" A chief judges "where do I send my people tonight?" Same core act —
reading a situation and choosing correctly — zoomed out. This is deliberate: it
means everything we build for the rookie loop keeps paying off up the ladder, and
it's how a solo team gets a whole career's worth of play out of one well-tuned core.

### 4.1 — The Three Nested Loops

The game runs on three loops, nested by timescale. The player lives mostly in the
innermost one; the outer two frame it and give it stakes.

**A. The Moment Loop (seconds to minutes) — a single interaction.**
One traffic stop, one call, one door knocked. This is where the game actually lives
and where Pillar 3 is won or lost.

**B. The Shift Loop (20–60 minutes) — a tour of duty.**
You clock on, work a sequence of moments (self-directed patrol + dispatched calls),
and clock off. The shift is the session-sized unit: a natural save/stop point, a
small arc with its own rhythm of quiet and spike, and the container that reputation
and consequence accumulate inside.

**C. The Career Loop (many shifts) — the spine.**
Shifts accrue into a record. The record earns rank, specialization, and story. This
is Section 5's territory; here it matters only as the thing that gives shifts a
direction. **Critically, the game must be fun at loop A alone** — the career loop is
the reason to keep going, never the reason it's fun in the first moment.

### 4.2 — The Moment Loop, In Detail (the heart of the game)

Every interaction, from a parking violation to a homicide scene, runs the same four
beats. This uniformity is a feature: it's a single, deep, learnable system that
scales in stakes rather than a pile of disconnected minigames.

1. **Observe.** The situation presents information, not instructions. A weaving car,
   a nervous answer, an open window on a "nobody's home" call, a detail in a
   statement that doesn't add up. The game does *not* tell the player what's wrong.
   Skill is noticing.
2. **Judge.** The player interprets. Is this a tired driver or an impaired one? A
   scared witness or a lying one? A domestic that's over or one about to reignite?
   This is the decision that authenticity (Pillar 5) makes meaningful — there's a
   *correct read*, it's earned by attention, and it's often ambiguous.
3. **Act (apply procedure).** The player chooses and executes the appropriate
   response: the right question, the field sobriety test, requesting backup, running
   the plate, making the stop vs. letting it go, drawing a weapon vs. keeping it
   holstered. Procedure is the verb set. Doing it in the right order, for the right
   reason, is the skill.
4. **Consequence.** The result lands and *sticks* (Pillar 4). A good read cleanly
   resolved builds reputation and record. A wrong read has costs — a wrongful stop
   dents community trust, a missed cue lets a situation escalate, a skipped step
   gets evidence thrown out later. Consequences are the game's real feedback signal,
   not an XP bar.

**What makes this fun without rewards (the Pillar 3 test):** the pleasure is the
*read* and the *clean execution* — the small satisfaction of correctly clocking
that something's off, handling it right, and watching it resolve. It's the tension
loop of a good detective show or a cooking game's "mise en place under pressure,"
not the dopamine drip of loot. If a moment isn't tense-or-satisfying with the reward
layer switched off, it's not shippable.

**The de-escalation principle.** Because the tone is grounded (Pillar 5), the
*default* and often *optimal* resolution is not force. Talking a situation down,
reading body language, choosing the calming question — these are first-class
mechanics with their own skill ceiling, not a lesser path. Force is available, has
weight, and carries heavy consequence. This is both an authenticity choice and a
design one: it keeps the moment loop about judgment, and it keeps a solo-scoped game
from having to lean on expensive, spectacle-heavy combat as its main verb.

### 4.3 — The Rookie Patrol Loop (the vertical-slice loop)

This is the loop Phase 1 must nail (Production Principle 3.1). A shift as a patrol
officer:

- **Clock on** at the precinct: light prep — check the board, pick a patrol zone or
  accept an assignment.
- **Patrol** your district. Self-directed downtime is *part of the design*, not dead
  air: you're scanning for the anomaly (Pillar 2 says this quiet beat has to be
  enjoyable on its own). Traffic enforcement, plate checks, presence.
- **Respond** when dispatch calls come in over the radio — a disturbance, a stop, a
  minor theft, a welfare check. Each is a Moment Loop.
- **Handle** the interaction through the four beats above: observe, judge, act,
  consequence.
- **Paperwork / close-out.** Lightweight but present — logging the stop, filing the
  report correctly. Authenticity (Pillar 5) lives here, but streamlined (Pillar 3):
  it's a satisfying "close the loop" beat, not a tax. Done well, this is where the
  player feels like a professional, not where they feel like a data-entry clerk.
- **Clock off.** Reputation, record, and any story threads update. The shift's
  results feed the Career Loop.

The full **rookie-to-first-promotion** arc built on top of this loop is the Phase 1
deliverable. If this loop is fun for an hour with no promotion in sight, the whole
project's core thesis is proven.

### 4.4 — How The Loop Evolves By Career Stage

Same four verbs, widening scope. Each stage adds a layer rather than replacing the
last (and per Pillar 2, the player can *stay* at any stage indefinitely and still
have a full game):

- **Patrol (rookie → officer):** the Moment Loop at street level. Stops, calls,
  presence. The foundation everything else is built from.
- **Investigation (detective track):** the Moment Loop stretched across *time*. A
  case is a sequence of moments — scene, canvass, evidence, interview — that the
  player assembles into a conclusion. Judgment shifts from "what's happening now" to
  "what happened, and can I prove it." (Detailed loop in Section 6.)
- **Specialist (vice, violent crimes, etc.):** the Moment Loop with a *domain flavor*
  and a story thread — same core act, colored by the specialization's texture and
  stakes.
- **Supervisor (sergeant):** a new **command layer** wraps the Moment Loop. You still
  work the street, but you also direct others, make calls on resource allocation,
  and own outcomes you didn't personally execute. Judgment scope widens from the
  incident to the team.
- **Command (lieutenant → chief):** the loop zooms fully out. The "situation" you
  read is the *district* or the *department*; the "procedure" is policy, deployment,
  and priorities. The player who wants this can have it; the player who never wants
  to leave the street never has to.

### 4.5 — Session Shape & Pacing

A healthy shift (Loop B) has a deliberate rhythm: stretches of low-stakes
self-directed patrol (calm, observational, the Pillar 2 "beat is enough" texture)
punctuated by dispatched spikes of tension (the Moment Loops that resolve into
consequence). We tune the *ratio* and *unpredictability* of that rhythm by feel in
playtesting (Principle 3.4) — too many spikes and it's exhausting and unrealistic;
too few and the quiet isn't yet carrying its weight and needs design attention, not
just more calls. The quiet carrying its own weight is the single hardest and most
important tuning problem in the whole game, because Pillar 2 lives or dies on it.

### 4.6 — Open Questions For This Section
*(Tracked here so we resolve them deliberately, not by accident.)*

- **Failure & death.** What happens when a moment goes badly wrong? Injury,
  suspension, a mark on the record — but almost certainly *not* permadeath or a hard
  "game over," since the career is the point. Needs a deliberate model (ties to
  Section 5 and Section 8).
- **Time structure.** Is the world on a persistent clock/calendar (shifts are days)
  or a looser session model? Affects Pillar 4 persistence and Section 12 saves.
- **Control & feel.** First- or third-person? Driving model fidelity? These are
  feel-defining and belong in a later feel/prototyping pass, not a design guess now.
- **The paperwork dial.** Exactly how much procedure is "authentic and satisfying"
  vs. "friction to streamline" is the Pillar 5 ↔ Pillar 3 tension in miniature, and
  it can only be settled by playtest.

---

## 5. Progression & Rank System (The Spine)

> This is the system that delivers Pillar 1 (your career is the story) and Pillar 2
> (every rank is a destination). It is modelled on the real NYPD structure but built
> for a **fictional city**, so we keep the authentic bones (Pillar 5) without the
> licensing or real-world-politics baggage.

### 5.1 — The Central Idea: Two Axes, Not One Ladder

Progression is a **grid, not a line.** The player occupies a point defined by two
independent axes:

- **Rank (vertical) — authority.** How much of the department you command, from a
  lone officer up to the Chief. This is the "rise through the ranks" spine.
- **Specialization (horizontal) — domain.** What *kind* of police work you do:
  patrol, homicide, vice, narcotics, etc. This is the "craft your own focus" fantasy.
  (Detailed in Section 6.)

This mirrors how a real department actually works, and it's the insight the source
material handed us: **Detective is not a command rank.** A senior detective outranks
no one — the title is domain and prestige, awarded *laterally* out of patrol, not a
step up the command chain. So "become a detective" and "get promoted to sergeant"
are two different moves in two different directions. A player can climb the rank axis,
slide along the specialization axis, or both. *A Homicide Sergeant and a patrol
Lieutenant are different characters, and the grid is what makes that true.*

### 5.2 — The Rank Ladder (Vertical Axis)

We compress the ~13 real ranks into **playable tiers**, where a tier exists only if
it meaningfully changes how the game plays (using the loop scopes from Section 4.4).
Titles that share a gameplay mode are folded together and re-exposed as *prestige
milestones* (see 5.4) so the fantasy survives without the content bloat.

| Tier | Real ranks folded in | Loop scope (from 4.4) |
|---|---|---|
| **1 · Police Officer** | Police Officer (grades 6th → 1st) | The street beat |
| **2 · Detective** *(lateral)* | Detective 3rd / 2nd / 1st Grade | Investigation loop — a specialization entry, **not** a promotion |
| **3 · Sergeant** | Sergeant | First command layer: lead a squad |
| **4 · Lieutenant** | Lieutenant | Multiple squads / a unit on a tour |
| **5 · Captain** | Captain | Command a precinct or specialized squad |
| **6 · Executive** | Dep. Inspector, Inspector, Dep. Chief, Asst. Chief, Bureau Chief | Command a borough/bureau |
| **7 · Chief of Department** | Chief of Department | **The capstone.** Highest uniformed member; runs the department |

**Chief of Department is the ceiling of the game** — the top of the arc the player
can reach. (The civilian Police Commissioner sits above it in reality but is an
appointed political office, not a career endpoint, so it's out of scope as a
playable rank.)

Note that Tier 2 (Detective) sits *between* Officer and Sergeant in this table only
for readability — mechanically it branches sideways off Tier 1, not upward. A
detective can later choose to enter the command ladder (Sergeant+), carrying their
specialization with them, or stay a detective for the whole game.

### 5.3 — Grades-Within-Rank: The Pillar 2 Engine

Every rank has **internal grades** (the real 6th→1st officer grades, 3rd→1st
detective grades, and equivalent sub-steps we define for the command tiers). This is
the mechanical heart of "every rank is a destination":

- A player who **never promotes** still has a visible, earned progression arc *inside*
  their current rank — climbing grades brings better assignments, more autonomy,
  higher pay, seniority, and reputation, all without a rank change.
- It means the answer to "is staying a beat cop for 100 hours a real game?" is
  **yes** — a career-long officer still has a five-grade journey, a growing record,
  and a reputation that reshapes the city (Pillar 4).
- Grades are the *slow, always-available* progression; promotions are the *occasional,
  optional, identity-changing* ones. The two run in parallel so there is always
  something to earn, whether or not the player wants to climb.

### 5.4 — Titles-as-Prestige: The Fantasy Without The Bloat

The executive echelon (Deputy Inspector through Bureau Chief) is **five titles for
one gameplay mode** — command. We build the single Executive command mode once, then
expose those titles as **prestige milestones** the player is promoted *through* on
the way to Chief. The result: the player gets the full "made Two-Star Chief" title
fantasy and ceremony, while we build one system instead of five.

General rule: **distinct gameplay tiers stay few (~5–6); earnable titles can be many.**
Titles are cheap (text, ceremony, UI); gameplay modes are expensive (systems). We
spend lavishly on the former and sparingly on the latter.

### 5.5 — How You Advance (The Currencies)

Advancement is earned through the *work*, never a raw XP bar (that would violate
Pillar 3). Three intertwined currencies, all outputs of the core loop:

- **Record** — the objective log of the job done: stops, cases closed, clearance
  rate, commendations, and also the black marks (thrown-out evidence, complaints,
  wrongful stops). This is the ledger Pillar 4 reads from.
- **Reputation** — how the player is *perceived*, split across at least two audiences
  that can diverge: **the department** (brass, peers) and **the community**. A cop
  can be loved by command and feared by a neighborhood, or vice versa. Specializations
  and command decisions push these around.
- **Merit / eligibility** — the gate for promotion and for entering a specialization:
  time-in-grade, a clean-enough record, sometimes an exam or an appointment (matching
  the real "detective is appointed, sergeant is examined" distinction, which is a
  nice flavor hook).

**Design rule:** these currencies are *consequences* of doing the work well, surfaced
as feedback — not a meter the player grinds. If we ever find ourselves designing a
task purely to "give the player some merit," we've broken Pillar 3.

### 5.6 — The "Stay Anywhere" Guarantee (Mechanical Support)

Pillar 2 is a *promise*, and this section is where we keep it mechanically:

- **No forced promotions.** Reaching promotion eligibility raises an *offer*, never an
  obligation. Declining is a first-class choice with its own narrative acknowledgement,
  not a dead end.
- **Content depth at every tier, not just the top.** Because grades (5.3) and
  specializations (Section 6) both operate at low ranks, a player who stops climbing
  still has horizontal and grade-wise progression to chase.
- **The world keeps responding regardless of rank (Pillar 4).** A veteran 1st-grade
  patrol officer is a known quantity on their beat — recognized, respected or resented
  — which is its own evolving story, independent of the command ladder.

### 5.7 — Open Questions For This Section

- **Command-tier grades.** The real ranks give us officer/detective grades for free;
  we need to *define* the internal sub-steps for Sergeant → Chief so those tiers get
  the same "always something to earn" texture. (Design task.)
- **Promotion friction.** Exam vs. appointment vs. merit-review — how much process do
  we simulate before it stops being authentic (Pillar 5) and starts being a chore
  (Pillar 3)? Playtest question.
- **Demotion / falling.** Can a bad enough record cost you rank or a specialization?
  Powerful for Pillar 4 stakes, but needs care so it doesn't feel punishing. Ties to
  the failure model in 4.6.
- **Rate of advancement.** How many shifts is a promotion? Sets the whole pacing of
  the career arc; tune by feel.

## 6. Specializations & Storylines

> The horizontal axis from Section 5. This is the "craft your own focus" fantasy and
> the home of the "storyline that follows you." It is also the section where solo-dev
> scope discipline (Principles 3.1, 3.2) matters most, because specializations are
> where content burden explodes if we're not ruthless.

### 6.1 — The Feasibility Trick: One Loop, Many Coats of Paint

Rank × specialization multiplies into dozens of possible identities (a Homicide
Sergeant, a Narcotics Lieutenant, a career Vice detective). That is only survivable
for one person because of Principle 3.2: **the observe → judge → procedure →
consequence loop is shared across every combination.** What changes per specialization
is only (a) *flavor* — the kinds of situations, the setting, the tools — and (b) a
small number of *hand-authored story beats*. We are not building thirty games; we are
building one loop, ~30 coats of paint, and roughly six hand-written story spines.

### 6.2 — The Four Categories (with Solo-Dev Triage)

The real department's units are **not one kind of thing.** They fall into four
categories that differ enormously in design fit and production cost. Triaging them is
what keeps the project shippable.

**A · Investigative Tracks — THE CORE.** *(Priority — these carry the storylines.)*
These are the focuses the original pitch was really about. They fit the investigation
loop (4.4) directly, and each is a candidate for hand-authored rank-up beats (3.2).

- **Homicide / Violent Crimes** — the marquee track; murders and serious assaults.
- **Vice** — trafficking, gambling, prostitution, liquor.
- **Narcotics** — street-level to distribution networks.
- **Warrants / Fugitive** — tracking and taking down wanted offenders.
- **Special Victims** — sex crimes, domestic and child/elder abuse. **⚠ Handle
  deliberately:** high authenticity value (Pillar 5), high risk if mishandled. This
  is an explicit later design decision, **not** a default inclusion, and never a
  Phase-1 slice.

**B · Tactical / Operational Units — FLAVOR, MOSTLY DEFERRED.**
These are different *activities*, not different *stories*, and several are budget
sinks for one person. Triage:

- *Cheap & high-flavor, keep as candidates:* **Highway** (reuses the driving/pursuit
  systems) and **K-9** (a companion mechanic).
- *Expensive, defer to Phase 3+ or cut:* **ESU/SWAT**, **Aviation** (a whole flight
  model), **Harbor** (boats), **Bomb Squad** (a bespoke defusal system), **SRG**,
  **Mounted**.

**C · Geographic Beats — SETTING, NOT SPECIALIZATION.**
**Transit** and **Housing** are not different jobs; they are the *same patrol loop* in
a new environment. That makes them ideal, cheap content for **horizontal world
expansion** (new districts that reskin the beat) rather than systems to build. They
belong to Section 7's world plan, not here.

**D · Counterterror / Intelligence — OUT OF SCOPE (for now).**
High concept, high cost, tonally distant from "rookie to chief." Defer or cut.

### 6.3 — How Specialization Works (Player-Facing)

- **Earned, not picked at menu.** You enter a specialization by proving yourself first
  on patrol and meeting eligibility (Section 5.5) — mirroring the real lateral
  appointment into the Detective Bureau. This makes the choice feel *earned*, and it
  means the patrol loop (Phase 1) is the on-ramp to everything.
- **A track you climb.** Within a specialization, the detective grades (3rd→1st)
  provide the grade-wise progression of Section 5.3 — so a specialist who never enters
  the command ladder still has a full arc.
- **Switchable, at a cost.** Changing focus is allowed (Pillar 1: your path is yours)
  but carries friction — reputation and momentum are partly domain-specific, so
  jumping from Vice to Homicide isn't free. This keeps choices meaningful without
  locking the player in.
- **Combinable with rank.** Entering the command ladder, you carry your specialization
  with you (a Homicide Sergeant supervises a homicide squad). This is the grid of 5.1
  made concrete.

### 6.4 — "A Storyline That Follows You" (Authored vs. Systemic)

This is the promise that must not become a project-killer. The model (detailed in
Section 9):

- The **bulk** of a specialization's cases are **systemically generated** with
  narrative flavor — an effectively endless supply of vice busts or homicides so the
  track never runs dry (supports Pillar 2's "play this forever").
- We **hand-author only the key beats**: the moment you're appointed, a recurring
  antagonist or thread that resurfaces as you climb the grades, and the specialization's
  capstone. A handful of authored anchors floating in a sea of systemic cases *reads*
  as a personal storyline without costing a full branching campaign per focus.

### 6.5 — Scope Sequencing (What We Actually Build, When)

- **Phase 1 (vertical slice):** patrol only — no specialization yet. Prove the beat
  (per 3.1 and Section 4.3).
- **Phase 2 (first specialization):** build **the Detective / investigation track
  first.** Rationale: it is the single biggest differentiator from *Patrol Officers*
  (which has no real career/investigation arc) and *The Precinct* (fixed story), and
  it proves the entire two-axis model works before we replicate it.
- **Phase 3+:** additional investigative tracks (Vice, Narcotics, …), then the cheap
  tactical candidates (Highway, K-9), then geographic expansion. Expensive tactical
  units and any decision on Special Victims come last, if at all.

### 6.6 — Open Questions

- **How many specializations ship at 1.0** vs. arrive as post-launch expansion? (The
  systemic-bulk model makes each *additional* one cheaper, which argues for a small
  launch set and steady additions.)
- **Do command-tier players lose the moment-to-moment specialization flavor,** or does
  a Homicide Captain still occasionally work a scene? (Ties to Pillar 2 at the top of
  the ladder.)
- **Special Victims:** in or out — and if in, what authenticity/safeguard framing?
  Deliberate decision, deferred.

## 7. World & Setting

> The world is not backdrop — it is the thing Pillar 4 acts on. Every decision here is
> chosen to make a *reactive* place feasible for one person, not to maximise map size.

### 7.1 — The Four Locks (committed)

- **A fictional, modern-day (2020s) city.** Contemporary tooling is part of the job:
  radios and CAD dispatch, body cameras, mobile data terminals, DNA and digital
  forensics, phone and camera evidence, records databases. This is a deliberate
  authenticity choice (Pillar 5) — modern police work *is* this tech, and it gives the
  investigation loop (Section 6) a rich, real toolkit.
- **A grounded mid-size American city.** Not a sprawling metropolis. Big enough to
  justify a full department with all the bureaus (Section 6), small enough that one
  person can make it *coherent and reactive* rather than merely large. Believability
  and memory beat scale — a smaller city the world actually remembers you in serves
  Pillar 4 far better than a bigger one that forgets you.
- **Framing: keep it about the work.** See 7.4 — the game foregrounds the *craft and
  judgment* of policing, not political advocacy.
- **Phase 1 slice: one mixed transitional district.** See 7.3.

### 7.2 — City Identity & Structure

**Character.** A believable second-tier American city with its own regional identity
— old industrial bones, a downtown that's half-revitalised, neighborhoods at
different points on the wealth and change curve. The kind of place with a real police
department, real problems, and a real texture, without being a stand-in for any one
actual city. **The city is Penrose Bay** — the name leans coastal/port, which gives us
a natural crime texture (a working waterfront, shipping, a harbor) and art palette to
build toward; finer regional flavor is still open (7.6).

**Scale philosophy.** We define the city as a **small set of distinct districts**
(target ~5–8, not dozens), each with a strong, legible identity, rather than a
seamless mega-map of interchangeable blocks. This is a direct application of
Principle 3.1 and Pillar 4: fewer, denser, more *memorable* districts are cheaper to
build and easier to make reactive than a large undifferentiated sprawl. Districts are
also the unit of **horizontal expansion** — the city grows district-by-district
across phases (Section 13), and each new one is a self-contained content drop.

**District identity as a design tool.** Because each district has a distinct
socioeconomic and physical character, the *same* patrol loop plays differently in
each — the mix of calls, the community-trust starting point, the kinds of crime — so
variety comes from *place*, not from bolting on new systems. This is how the
grounded mid-size city stays interesting without ballooning in scope.

**Geographic beats fold in here (from 6.2-C).** Transit and Housing are not separate
specializations — they are **district reskins of the patrol loop**: a subway/transit
network and public-housing developments are *places* with their own call texture, not
new jobs. They arrive as expansion districts, reusing the core loop.

### 7.3 — The Phase 1 District (the Vertical Slice's home)

The slice is built in **one mixed transitional district** — the single most useful
kind of neighborhood for proving the beat. It deliberately contains variety in a
contained footprint:

- A **commercial strip** (shops, bars, traffic, minor theft, disturbances).
- **Residential blocks** (welfare checks, domestics, neighbor disputes, the
  recurring-faces texture that feeds Pillar 4).
- **Rough edges / a district in flux** (a gentrifying seam, some vacant property) —
  giving room for a range of severity without needing the whole city.

This one district is designed to exercise **every beat of the Moment Loop (4.2)** and
the full **rookie-to-first-promotion arc (4.3 / Section 5)** end to end. If the game
is fun in this one neighborhood, the core is proven and horizontal expansion is
"more of a known-good thing," not a leap of faith. *(Working name TBD.)*

### 7.4 — Political Framing: "Keep It About The Work" (stated deliberately)

This has been flagged since the concept stage as a decision to make on purpose rather
than stumble into. **The commitment: the game is about the craft and judgment of the
job, not a piece of political advocacy in either direction.** Concretely:

- **Foreground:** procedure, discretion, evidence, de-escalation, the weight of
  individual decisions, the human texture of the people an officer meets. The drama
  is *situational and personal* — this call, this person, this choice — not thematic
  argument.
- **We do not pretend total neutrality.** A game about rising through a police
  department inevitably *implies* things; honesty (and our own stated evenhandedness)
  means we acknowledge that rather than claim a nonexistent objectivity. What "keep it
  about the work" means is that **systemic political questions are ambient texture,
  not the subject** — present in the world's realism (community trust varies by
  district, a bad stop has consequences, corruption exists as a situational hazard),
  but never editorialised into a message the game is trying to sell.
- **Consequence carries the ethics.** Rather than *telling* the player what's right,
  the reactive city (Pillar 4) *shows* it: cut corners and community trust erodes and
  cases fall apart; play straight and it compounds differently. The moral content is
  *emergent from consequence*, which is both less preachy and more in keeping with the
  grounded-sim tone.
- **This is a living decision.** If, in playtesting, "about the work" starts to feel
  like *dodging* rather than *focusing*, we revisit — but the default is set.

### 7.5 — World Systems That Serve Pillar 4 (pointers to Section 8)

The setting only matters if it *reacts*. The systems that make it do so are speced in
Section 8, but the world section names what they must deliver:

- **A persistent record & reputation the city reads from** (Section 5.5) — recognition,
  respect or resentment that varies by district.
- **Day/night and a time structure** — a mid-size city on a shift/clock rhythm (the
  open question from 4.6 lands here too).
- **Reactive districts** — community-trust state per district that visibly shifts with
  the player's conduct.

### 7.6 — Open Questions

- **Regional flavor** — name is set (**Penrose Bay**, leaning coastal/port); still to
  nail the finer texture: gritty working harbor vs. faded resort town vs. mixed, and
  the art palette that implies.
- **How many districts at 1.0** vs. added later — ties to the roadmap (Section 13).
- **Map traversal** — drivable seamless city vs. district hubs with fast travel. A
  feasibility-vs-immersion call that touches Section 12; the grounded mid-size scale
  keeps both options open.
- **Real-city inspiration blend** — how much we borrow the *feel* of specific cities
  without becoming any one of them.

## 8. Core Systems

> These are the engines under the hood. None of them is an end in itself — each exists
> to serve the loop (Section 4) or to make the city *remember* (Pillar 4). Two rules
> govern this whole section: **(1)** per Principle 3.3 we *buy or borrow* the solved
> problems (traffic, crowds, pathfinding, streaming) and spend our own time only on
> the systems that make *this* game unique; **(2)** the systems are deliberately built
> to **share a few common data structures** — the Record, the Reputation state, and
> the World state — so that "a dozen systems" is really one flywheel wearing several
> faces. That shared spine (8.8) is what makes this tractable for one person.

### 8.1 — Reputation System (the two-audience model)

Reputation is the currency Pillar 4 spends. Per Section 5.5 it is **not a single
meter** — it splits across audiences that can diverge, which is the whole point:

- **Department standing** — how the brass and your peers see you. Driven by closed
  cases, clean procedure, commendations; damaged by complaints, thrown-out evidence,
  insubordination. Gates promotion and specialization access (Section 5).
- **Community trust — tracked *per district*** (Section 7.2). Driven by how you treat
  the people on your beat: fair stops, de-escalation, showing up for the small calls;
  eroded by heavy-handedness, wrongful stops, corner-cutting. This is the number that
  makes two playstyles produce two visibly different cities.

**Mechanics:** each is a slow-moving state, not a twitchy bar — nudged by the
*consequence* beat of the Moment Loop (4.2), never awarded as a raw "reputation point"
pickup (that would break Pillar 3). Effects are **diegetic**: high community trust
means witnesses talk to you, tips come in, crowds cooperate; low trust means silence,
hostility, and cases that stall for lack of cooperation. High department standing
means better assignments and latitude; low standing means scrutiny and desk duty. The
two can pull apart — a cop adored by command and feared by a neighborhood is a
*character*, and the systems let the player become one on purpose or by drift.

### 8.2 — Evidence & Investigation Mechanics (the marquee system)

This is the system that most differentiates the game (Section 6) and where
authenticity (Pillar 5) is most load-bearing. The investigation loop from 4.4
stretches the Moment Loop across time; this section gives it teeth. A case is
assembled, not handed over, in five procedural stages:

1. **Scene** — secure it, observe it (Observe beat), collect physical evidence. Doing
   this *correctly and in order* matters — a contaminated or improperly handled scene
   costs you later.
2. **Canvass & interview** — witnesses, suspects, statements. The Judge beat: reading
   truth from evasion, spotting the detail that doesn't fit. Community trust (8.1)
   directly gates how much people cooperate.
3. **Analysis** — forensics, records, digital/phone/camera evidence (modern-day
   toolkit, Section 7.1). Turns raw evidence into leads.
4. **Connect** — the player assembles evidence and testimony into a theory of the case
   on a **case board** (Section 11 UI). This is the core detective *verb*: forming and
   testing the read, not being told the answer.
5. **Resolve** — build enough to justify a warrant/arrest and make it *stick*. The
   authenticity hook: a sloppy chain — skipped procedure, a bad-faith stop, weak
   evidence — means the case falls apart downstream (thrown out, no charge), which
   feeds back into the Record and Reputation as a *failure with teeth*, not a reload.

**Feasibility note:** the *bulk* of cases are systemically generated (Section 9);
this section defines the **verbs and rules** the player applies to any case, authored
or generated. We build the investigation *system* once; content flows through it.

### 8.3 — Dynamic Police-Response System

The world's police apparatus — dispatch, backup, escalation — modeled as a living
system rather than scripted set-pieces. It does two jobs:

- **Feeds the player work.** A CAD/dispatch layer (Section 7.1) surfaces calls over
  the radio, prioritized and distributed across the district. This is the tap that
  fills the Shift Loop (4.1B); its *rhythm* is the pacing dial from 4.5.
- **Responds to situations.** Backup, supervisors, and specialized units arrive
  according to severity and the player's own calls for support. At **command tiers**
  (Section 5.2), the player flips to the *other side* of this system — they *are* the
  one allocating the response, which is what the command loop (4.4) actually is.

Escalation is grounded (Pillar 5): a routine stop that goes wrong pulls a realistic,
tiered response, not a GTA-style wanted-star spiral. Force and pursuit exist and carry
weight, but the default texture is procedural, not action-movie.

### 8.4 — NPC & World AI Behavior (two tiers)

We split AI sharply, because conflating the two is how solo scope dies:

- **Ambient AI (buy/borrow — Principle 3.3):** traffic, crowds, pedestrian
  pathfinding, background city life. These are *solved* off the shelf (engine-native
  crowd/traffic systems, sample-city tech). We tune, we don't build. Their only job is
  to make Penrose Bay feel alive.
- **Reactive AI (bespoke — where we spend):** the actors *inside* a Moment Loop — the
  nervous driver, the evasive witness, the suspect deciding whether to run, comply, or
  fight. These carry **judgment-bearing behavior**: readable tells, believable
  responses to the player's approach (a calm question vs. a hard order), de-escalation
  that can actually work. This is the AI that makes the Observe/Judge beats (4.2) real,
  and it's worth hand-crafting because it *is* the core of the game.

The line between them is deliberate: ambient AI is set dressing we get cheaply;
reactive AI is the expensive, unique part, and we concentrate effort there.

### 8.5 — Time, Shifts & Day/Night

Resolving the open question from 4.6 with a committed default: **the world runs on a
persistent clock and calendar; shifts are the play unit.** The player clocks on for a
tour of duty (4.1B), and time advances across days. Rationale:

- It makes the shift a natural **session and save boundary** (4.1B) and gives the
  career arc a felt sense of *time served* (which the grade system, 5.3, reads from).
- **Day/night and shift assignment change the incident mix** — a night tour in the
  commercial strip is a different job from a day tour, giving variety from *time*
  rather than new systems (the same cheap-variety principle as districts, 7.2).
- Persistence is what lets the city *remember* between shifts (Pillar 4).

*(Open sub-question: does time pass only on-shift, or does the world simulate
off-shift too? Leaning "world advances, lightly" — see 8.9.)*

### 8.6 — Economy (deliberately restrained)

⚠ **This is the section with the most genuine design fork — flagged for a decision.**
A police-career sim could support several very different "economies," and they are not
equally good for *this* game. The recommended stance keeps it grounded (Pillar 5) and
avoids turning the game into something it isn't:

- **Recommended: a light personal/career economy.** Salary scales with rank and grade
  (Section 5) — a quiet reinforcement of progression, spendable on modest,
  character-flavor things (gear, a better car, an apartment) — *not* a loot/shopping
  treadmill. Money is a texture of the career, not a goal that competes with the job.
- **At command tiers: a resource/deployment layer, not cash.** A Captain/Chief manages
  *people and priorities* (where to deploy, what to prioritize), which is the command
  loop's real content — an "economy" of finite police resources, not a wallet.
- **Explicitly NOT building:** a criminal-empire/black-market economy, or a
  city-simulation macroeconomy. Both are out of tone and out of scope.

If the player-facing progression already feels rich from rank + grade + reputation, we
could even cut a personal economy to near-zero. **Decision deferred — see 8.9.**

### 8.7 — Failure & Consequence Model (from 4.6)

The design commitment: **no hard "game over," no permadeath.** The career *is* the
game, so failure must be something you *carry*, not something that ends the run. Stakes
are graduated and persistent, drawn from the systems above:

- **Botched moments** dent community trust (8.1) and can escalate a situation, but you
  live on.
- **Injury** costs downtime/recovery — a real setback with time-cost, not a reset.
- **Bad procedure** blows cases downstream (8.2) — evidence thrown out, no charge — a
  loss that shows up in the Record.
- **Complaints / misconduct** hit department standing (8.1), invite scrutiny, and at
  the extreme risk **suspension or demotion** (the falling question from 5.7) — the
  ladder can go *down*, which is what gives climbing it weight.
- **Death of the player character**, if it exists at all, resolves as hospitalization
  and consequence, not a fail-state screen — to be settled in prototyping.

The throughline: consequences are **feedback the world gives you**, persistent and
legible, which is exactly the "live with the result" beat of the Moment Loop scaled up
to a career. This is Pillar 4 with stakes attached.

### 8.8 — How It All Interlocks (the flywheel)

The critical thing for a solo build: these are not seven separate systems, they are
**one loop feeding a shared spine.** The cycle:

> **Moment Loop (4.2)** produces an outcome → written to the **Record** → which moves
> **Reputation** (dept + per-district community, 8.1) → which changes **World state**
> (who cooperates, what assignments open, how the district feels) → which reshapes the
> **next incidents** the dynamic-response system (8.3) and reactive AI (8.4) generate →
> which the player meets in the next Moment Loop.

Three shared data structures — **Record, Reputation, World state** — are read and
written by every system here. Progression (Section 5) reads the same spine to gate
rank and specialization. Build that spine well once, and the systems compose instead of
multiplying. This diagram *is* the game.

### 8.9 — Open Questions

- **Economy scope (the big one):** light personal economy, command-tier resource layer
  only, or near-zero? (8.6) — pick before building any wallet UI.
- **Off-shift simulation:** does the world evolve while the player is clocked off
  (crimes occur, cases age, trust drifts), or is it frozen between shifts? Affects
  Pillar 4's depth and Section 12's persistence cost.
- **Reputation granularity:** is community trust a single per-district value, or
  further split (e.g., by community vs. business vs. specific factions)? Start simple,
  expand only if it earns its keep.
- **Simulation depth vs. legibility:** how deep the reactive-AI tells go before they
  stop being *readable* by the player and start being noise — a Pillar 3 / playtest
  question.
- **Death handling:** the one genuinely unresolved consequence case (8.7), for
  prototyping.

## 9. Content Strategy (Authored vs. Systemic)

> This is the section that decides whether the project is *buildable at all*. The
> original concept's most dangerous promise — "each focus has a storyline that follows
> you" — becomes a project-ending trap if read as "hand-write six branching campaigns."
> This is the model (Principle 3.2) that delivers the *feeling* of that promise at a
> cost one person can actually pay.

### 9.1 — The Three Content Layers

All content in the game comes from one of three layers, and the *ratio* between them
is the whole trick:

- **Layer 1 — Systemic bulk (≈90%).** The endless supply: patrol calls, traffic stops,
  generated cases. Procedurally assembled, narratively flavored, effectively infinite.
  This is what makes "play a beat cop for 100 hours" (Pillar 2) possible — the well
  never runs dry.
- **Layer 2 — Authored anchors (≈10%, but where the soul lives).** A small, curated set
  of hand-written beats: the moment you're appointed to a specialization, a recurring
  antagonist or thread that resurfaces as you climb, the specialization's capstone, key
  rank-up ceremonies. These are cheap in *volume* but rich in *meaning*.
- **Layer 3 — Emergent (free).** Content the flywheel (8.8) produces at no authoring
  cost: a district that's turned hostile because of your conduct, a witness who won't
  talk because of your reputation. Nobody writes this; it *happens* because the systems
  interact. It's the highest-value content per dollar because the dollar is zero.

**The illusion that makes it work:** a handful of authored anchors (Layer 2) floating
in a sea of systemic cases (Layer 1), tied together by an emergent, reactive world
(Layer 3), *reads* to the player as "a personal storyline that followed me" — without
anyone having written that specific story. Pillar 1 delivered by arithmetic, not by a
writers' room.

### 9.2 — How Procedural Cases Are Generated (the grammar)

A case is not free-form text — it's a **structured object assembled from pools**, with
a guaranteed-solvable logical skeleton. The generator builds, roughly:

- **A crime** (type, severity) → drawn from the specialization/district-appropriate pool.
- **A truth** — who did it, motive, sequence of events. Generated *first and privately*,
  so the case has a real answer.
- **An evidence chain** — the generator lays down a *solvable trail* backward from the
  truth: physical evidence at the scene, witnesses with partial knowledge, records that
  corroborate or mislead, red herrings. Crucially, it guarantees the trail is
  *followable* — the case is always fair.
- **A cast & locations** — victim, suspects, witnesses, drawn from NPC pools and placed
  in real district geography (Section 7).
- **A flavor pass** — names, specifics, district context, dossier text layered on top so
  two structurally identical cases *feel* different.

The player never sees the skeleton; they experience it through the investigation loop
(8.2) — scene, canvass, analysis, connect, resolve. The generator's job is to guarantee
every case is **coherent, solvable, and fair**; the flavor layer's job is to make it
feel particular.

### 9.3 — Where Authored Beats Slot In

Authored content is triggered by **progression state**, not by a linear script:

- **Appointment beats** — entering a specialization opens with an authored scene.
- **Recurring threads** — a named antagonist, an unsolved cold case, a departmental
  rivalry that *resurfaces* at set career milestones, woven between systemic cases so it
  feels like a through-line.
- **Capstones** — each specialization and the road to Chief end on authored, higher-
  production beats.
- **Rank ceremonies** — promotions get authored acknowledgement (cheap: mostly text and
  staging), which is what makes "titles-as-prestige" (5.4) land emotionally.

The design rule: **author the beats the player will remember, generate everything they
won't.** A player remembers making detective and catching the antagonist who's haunted
their career; they don't remember the 60th shoplifting call — so we write the former and
generate the latter.

### 9.4 — Narrative Flavor Without Full Branching / VO

Grounded scope demands we deliver "story" cheaply:

- **Text-forward delivery** — case files, dossiers, radio chatter, MDT records (Section
  11). Text and structured data are radically cheaper than cinematics and scale
  effortlessly with systemic content.
- **Templated systemic text, bespoke authored text** — Layer 1 uses parameterized
  templates; Layer 2 gets hand-written prose. Voice acting, if any, is reserved for the
  few authored anchors, never the infinite systemic bulk.
- **Consequence as narrative** — much of the "story" is the reactive world (Layer 3), not
  written words at all. This is the cheapest storytelling there is and the most in keeping
  with the grounded tone.

### 9.5 — Tooling Needed (the real deliverable of this section)

The generator and anchors are only sustainable if **adding content is cheap**, which
means the game must be **data-driven** (see Section 12):

- **A case/incident authoring tool or data format** — designers (i.e. the solo dev) add
  crime types, evidence templates, NPC pools, and district tables *as data*, no code
  changes. This is the single highest-leverage tool in the project.
- **Pool/table management** — the flavor pools (names, motives, locations) live in
  editable tables so the world's variety grows by data entry.
- **An anchor-beat scripting path** — a lightweight way to bind authored scenes to
  progression triggers.
- **A "case validator"** — tooling that auto-checks a generated case is actually solvable
  before it ever reaches the player (protects fairness at scale).

Building these tools *is* Phase 2 work (Section 13), because they're what turn "content"
from a per-item hand-cost into a renewable system.

### 9.6 — Open Questions

- **How much LLM/generative assistance in flavor text** — modern tooling could generate
  case-flavor prose; tempting for volume, but risks tonal drift and needs guardrails.
  Deliberate decision, deferred.
- **Cold-case / long-arc persistence** — how long a recurring thread can span without
  becoming incoherent across a nonlinear career.
- **Generation tuning** — difficulty and fairness of generated cases is a deep
  playtest-by-feel problem (Principle 3.4).

## 10. Art Direction & Audio

> Art is the single biggest *volume* risk for a solo dev (Section 14). Every choice here
> is made to get a coherent, grounded look **without** one person modelling a city by
> hand. The locks: **stylized realism**, produced **marketplace-heavy + kitbash**.

### 10.1 — Visual Target: Stylized Realism

Believable, grounded Penrose Bay — readable and characterful, but *slightly* stylized
rather than chasing photoreal. This is a deliberate feasibility choice as much as an
aesthetic one:

- It **matches the grounded-sim tone** (Pillar 5) — the world reads as real and serious —
  while staying **forgiving of asset limitations** in a way full photorealism never is.
- It keeps the bar at "coherent and atmospheric," not "flawless," which is the only bar a
  solo dev can actually clear across a whole city.
- Readability is a *gameplay* requirement here, not just taste: the Observe/Judge beats
  (4.2) depend on the player being able to *read* a scene, so clarity beats visual noise.

### 10.2 — The Coherence Problem (and the house-style fix)

Marketplace-heavy production has one signature failure mode: a kitbashed world looks
like a bag of mismatched assets. The mitigation is a strong, unifying **"house style"**
applied *over* the bought assets:

- **A consistent lighting and color-grade identity** — a signature post-process, palette,
  and lighting mood that ties disparate assets into one place. This is where a solo dev
  gets the most identity per hour: unifying light and color is far cheaper than custom
  modelling and does more for coherence.
- **Time-of-day and weather as mood tools** (tying to 8.5) — Penrose Bay's coastal
  setting (fog, wet streets, harbor light, overcast) is both an identity and a
  cheap-atmosphere generator that further masks asset seams.
- **Restraint** — a tighter, curated material and palette range reads as *intentional*;
  sprawling visual variety reads as *bought*.

### 10.3 — Asset Production Strategy (Principle 3.3 applied)

- **Buy/borrow the bulk:** environments, props, vehicles, background characters, and the
  city fabric come from the marketplace and sample-city tech (Section 12). We *curate and
  unify*, we don't build from scratch.
- **Spend custom effort only where it counts:** signature/hero locations (the precinct,
  key story sites), gameplay-critical assets (evidence items that must read clearly), and
  recurring named characters. Everything the player scrutinizes gets love; everything they
  pass gets kitbashed.
- **Characters via Metahuman + marketplace** (Section 12) — a major solo lever for
  getting believable, animatable people cheaply, with animation retargeting for reuse.

### 10.4 — Audio Direction: Dispatch-Led

For a police game, **audio carries more immersion per dollar than visuals** — and it's
far cheaper for one person. So audio is a *primary* identity tool here, not an
afterthought:

- **Radio/dispatch chatter is the signature soundscape.** The constant, textured hum of a
  working department — calls, codes, cross-talk — does enormous work for authenticity
  (Pillar 5) and mood, and it's largely *audio*, not expensive animation. This is the
  game's sonic signature.
- **A living-city ambient bed** — traffic, gulls and harbor tones (Penrose Bay), crowds,
  weather — layered and reactive to district and time (8.5).
- **Restrained, tension-driven score** — sparse by default, rising for the spikes (4.5).
  Grounded games are served better by *tension and space* than a wall-to-wall soundtrack,
  which also happens to be cheaper.
- **Solo audio strategy:** high-quality sound libraries for SFX and ambience; minimal
  original composition; VO reserved strictly for authored anchors (9.4), with systemic
  dispatch lines assembled from a recorded/parameterized pool rather than bespoke acting.

### 10.5 — Open Questions

- **Exact stylization dial** — how far from photoreal (subtle vs. overt) is a look-dev/
  prototyping decision, tuned once the house style is on real assets.
- **Character fidelity vs. count** — Metahuman quality vs. crowd performance budget
  (ties to 8.4 / Section 12).
- **Camera perspective still open (4.6)** — first vs. third person materially affects
  character-art investment and animation needs; deferred to feel-prototyping.

## 11. UI / UX

> UI in this game is not chrome — several of its screens *are* the gameplay (the case
> board is the detective loop; the report flow is the close-out beat). The governing
> bar, from 4.3: **procedure must feel professional and satisfying, never like a tax.**

### 11.1 — Design Principles

- **Diegetic-first.** Wherever possible, the interface is an in-world object — the radio,
  the mobile data terminal (MDT), the case board — not an abstract menu. This serves the
  grounded tone (Pillar 5) and makes the UI part of the fantasy of *being* the officer.
- **Friction is designed, not accidental.** Authenticity sometimes *wants* a few
  deliberate steps (it's what makes you feel like a professional); tedium is friction with
  no payoff. Every procedural step must earn its place with a "close the loop"
  satisfaction. This is the Pillar 5 ↔ Pillar 3 dial (4.6) rendered in UI.
- **Legibility over density.** Reusable, few, clear screens — both a usability and a
  solo-scope requirement (UI is a notorious time sink; Section 14).

### 11.2 — The Key Surfaces

- **Radio / dispatch.** The incoming-work interface (feeds the Shift Loop, 8.3). Minimal,
  audio-led (Section 10.4), diegetic — accept/route calls without leaving the world.
- **The MDT (Mobile Data Terminal).** The in-world hub for records, plates, warrants,
  case files, and the database toolkit of modern policing (7.1). Diegetic and central —
  it makes "running the check" a tactile in-fiction action rather than a menu dive.
- **The Case Board — the marquee UI.** The interactive surface where the *Connect* beat
  (8.2) happens: evidence, statements, and leads pinned and linked into a theory of the
  case. This is the core detective *verb* made tangible; it must be tactile and
  satisfying to manipulate, because for the detective specialization this screen is the
  game. Highest UX-craft investment in the project.
- **Report / paperwork flow.** The close-out beat (4.3). Streamlined with smart defaults
  and structure — you make *judgments* (charge/warn/release, which statute), you don't do
  data entry. Authenticity via meaningful choices, not clerical volume. Getting this to
  feel like *professional closure* rather than *homework* is a specific, deliberate design
  goal.
- **Rank / career dashboard.** The progression-legibility screen — record, department
  standing and per-district community trust (8.1), grade progress (5.3), specialization
  track, and the road to the next rank. This is the "look how far I've come" surface that
  makes Pillars 1 and 2 *felt*; it must read as a career, not a stat sheet.
- **Map.** District-based (Section 7), showing active calls, case locations, patrol
  zones, and district community-trust state at a glance.

### 11.3 — Open Questions

- **Camera perspective (4.6)** cascades into UI (diegetic HUD vs. screen-space) — deferred
  to prototyping.
- **How much of the MDT/records depth is fun vs. friction** — a core playtest dial.
- **Case-board complexity ceiling** — how intricate link-analysis can get before it loses
  the "satisfying, not fiddly" line.

## 12. Technical Architecture

> The architecture exists to serve two masters: the **flywheel spine** (8.8) and
> **solo velocity**. Every choice favors leveraging solved technology (Principle 3.3)
> and keeping content data-driven (Section 9) over building from scratch.

### 12.1 — Engine: Unreal Engine 5

Committed. It is the right fit for this specific project, not just a default:

- **The open-world "solved problems" ship with it.** Mass AI / MassTraffic (ambient
  crowds and traffic, 8.4), World Partition (streaming the city), and the City Sample
  as reference/kitbash source directly cover the systems Principle 3.3 says we must *not*
  reinvent.
- **Metahuman + animation retargeting** give a solo dev believable, reusable characters
  cheaply (Section 10.3).
- **Nanite + Lumen** do much of the "stylized realism" lighting/detail work (Section 10)
  with far less hand-optimization than older pipelines.
- **A deep marketplace ecosystem** is the backbone of the kitbash asset strategy (10.3).
- **Blueprints + C++** let one person move fast (Blueprint) while dropping to C++ for the
  performance-critical bespoke systems (reactive AI, the case generator).
- Aligns with the project's existing environment (UE 5.8).

### 12.2 — Off-The-Shelf, Leveraged Deliberately

Buy/borrow: MassTraffic/MassAI, World Partition streaming, City Sample tech, Metahuman,
marketplace environments/props/vehicles, animation libraries + retargeting, and
State Tree/Behavior Tree frameworks for the *reactive* AI (8.4). Build ourselves *only*:
the reactive-AI behavior that carries judgment (8.4), the case generator (9.2), the
career/reputation spine (8.8), and the bespoke UI surfaces (Section 11).

### 12.3 — Data-Driven Content Architecture (the backbone)

The content model of Section 9 only works if content is **data, not code**:

- Crime types, evidence templates, NPC/flavor pools, district tables, dialogue, reputation
  rules, and rank/grade definitions all live as **Data Assets / Data Tables**, editable
  without recompiling.
- The **case generator** consumes this data to assemble solvable cases (9.2); the
  **case validator** (9.5) runs as a build/authoring-time check.
- This is what makes adding a specialization or a district a *content* task, not an
  *engineering* task — the core lever for solo sustainability.

### 12.4 — Save / Persistence (critical for Pillar 4)

The whole game's memory is the flywheel spine, so persistence is a **first-class,
build-it-early system**, not a late add:

- **Serialize the spine — Record, Reputation, World state (8.8) — robustly and from day
  one.** Per-district community trust, department standing, case history, career/rank/
  grade state, and world flags must all survive across shifts and sessions. Pillar 4
  *is* this save system working.
- **Design for a long-lived project:** versioned save format with migration, so a career
  save isn't broken by later content updates — essential for a multi-year, phased build
  where players (and the dev) carry saves across versions.
- **Persistence scope ties to the 8.9 open question** (does the world evolve off-shift?) —
  the answer sets how much state must be simulated and stored.

### 12.5 — Performance Strategy

The 8.4 concern — many systems running at once — is the real technical risk (Section 14):

- **Budget the bespoke systems** (reactive AI, generation) against the borrowed ones
  (Mass crowds/traffic), and **profile early and continuously** rather than at the end.
- The **grounded mid-size scale** (7.1) is itself a performance mitigation — a smaller,
  denser city is far more tractable than a sprawling one.
- Reactive-AI count is capped/streamed so judgment-bearing NPCs exist where the player is,
  with ambient AI filling the rest.

### 12.6 — Solo Pipeline & Tooling

- **Source control built for game assets** (Perforce or Git LFS) — non-negotiable for a
  multi-year solo project; protects against the catastrophic single-machine loss.
- **The content-authoring tools** of 9.5 are themselves core deliverables.
- **AI coding assistance** as an accepted force multiplier (per the project's own
  premise) — used to compress the "I don't know how to do X" friction, with the human
  owning architecture, integration, and the irreplaceable *tuning-for-fun* (Principle 3.4).

### 12.7 — Open Questions

- **Traversal model (7.6):** seamless drivable World Partition city vs. district hubs with
  fast travel — a streaming-cost vs. immersion tradeoff.
- **Off-shift simulation cost (8.9)** — directly sizes the persistence and sim budget.
- **How much C++ vs. Blueprint** for the bespoke systems — a velocity vs. performance
  balance settled by profiling.

## 13. Development Roadmap & Milestones

> **Capability-gated, not date-gated.** With no deadline (a passion project), phases
> advance when a capability is *proven*, not when a calendar says so. Each phase ends on
> a **playable, evaluable state** (Principle 3.4) — the project is never a pile of
> unfinished systems, it's always something you can pick up and feel. The ordering is
> the entire risk strategy: fun first and smallest first (Principle 3.1).

### Phase 0 — Foundations & the "Is It Fun?" Prototype
*Goal: prove the Moment Loop feels good before building anything around it.*
Engine setup (UE5), source control, the spine data structures (8.8) in skeleton form.
A greybox single interaction — one traffic stop or one call — running the full
Observe → Judge → Act → Consequence beat (4.2). **Gate:** is the raw interaction
tense/satisfying with zero rewards attached (the Pillar 3 test)? If no, iterate here;
build nothing else until yes.

### Phase 1 — The Vertical Slice (the make-or-break milestone)
*Goal: the complete rookie experience, fun end to end, in one neighborhood.*
The mixed transitional district (7.3), the rookie patrol loop (4.3), and the full
**rookie-to-first-promotion** arc (Section 5). The flywheel spine working end to end —
Record → Reputation → World state → next incidents (8.8) — plus robust save/persistence
(12.4). Ambient AI bought-in (8.4), reactive AI bespoke for the slice's interactions.
**Gate:** is one hour on this beat fun with the promotion carrot removed? This phase is
the whole project's thesis; nothing expands until it holds.

### Phase 2 — The First Specialization + the Content Engine
*Goal: prove the two-axis model and the content model that make the game scalable.*
Build the **Detective / investigation track** (the biggest differentiator, per 6.5),
the **case generator + validator** (9.2, 9.5), the **case board UI** (11.2), and the
first **authored anchor beats** (9.3). This is where "systemic bulk, authored beats"
stops being a plan and becomes a working machine. **Gate:** can the generator produce
coherent, fair, replayable cases, and does a hand-authored anchor read as "my story"?

### Phase 3 — Horizontal Expansion
*Goal: turn the proven core into a full game, cheaply, using the engines from Phases 1–2.*
More districts (including Transit/Housing reskins, 6.2-C/7.2); more investigative
specializations (Vice, Narcotics — each cheaper than the last thanks to the Phase 2
engine); the command tiers (Sergeant → the road toward Chief, Section 5). Content grows
mostly as *data* (Section 12.3).

### Phase 4 — Depth, the Ceiling, and Polish
*Goal: complete the arc and the feel.*
The full rank ladder up to **Chief of Department**; cheap tactical candidates (Highway,
K-9, 6.2-B); the economy decision resolved and implemented (8.6); tuning passes on
pacing (4.5), generation fairness (9.6), and the house-style art coherence (10.2).

### Post-Launch / Ongoing
Additional specializations (the systemic model makes each incremental one inexpensive);
the deferred heavy tactical units (ESU, Aviation, etc.) only if ever justified; the
Special Victims decision (6.2) if taken up, with its required care.

### Roadmap Notes
- **Every phase is shippable-as-experience** — even Phase 1 alone is a complete small
  game (a rookie in one district), which de-risks motivation: there is always a real
  thing to show and play.
- **Later phases reuse earlier engines**, so velocity *increases* over time — the
  expensive foundational work is front-loaded, the cheap content-driven work is back-
  loaded. This is the shape that survives a long solo timeline.

## 14. Scope Management & Risk Register

> A living list. Each risk has a **severity** (for a solo, no-deadline project) and a
> **mitigation already built into the design**. The recurring theme: most risks here are
> answered by a decision made earlier in this document — which is the point of having
> made them deliberately.

| # | Risk | Severity | Mitigation (and where it lives) |
|---|---|---|---|
| R1 | **Content volume** — an open world + endless cases is a bottomless authoring pit | **Critical** | Systemic generation for the ~90% bulk (Section 9); kitbash/marketplace art (10.3); district-by-district growth (7.2, Phase 3). Author only what's remembered. |
| R2 | **Motivation over time** — the true killer of solo, no-deadline projects | **Critical** | Vertical-slice-first so it's *fun early* (3.1, Phase 1); every phase is playable (Section 13); each phase is a shippable small game. Momentum treated as a design requirement. |
| R3 | **Open-world integration & performance** — many systems at stable framerate | **High** | Buy/borrow solved systems (3.3, 12.2); World Partition; profile early (12.5); grounded mid-size scale as a deliberate perf choice (7.1). |
| R4 | **The parallel-storylines trap** — the original concept's most dangerous promise | **High** | "Systemic bulk, authored beats" (3.2) fully speced (Section 9); the 90/10 layer model; no six hand-written campaigns, ever. |
| R5 | **Scope creep** — the slow death of ambition-rich projects | **High** | The 5 pillars as active decision filters; titles-not-tiers (5.4); explicit "NOT building" lists (6.2-D, 8.6); this risk register itself. |
| R6 | **Save/persistence complexity** — Pillar 4 depends on it, and it's easy to bolt on too late | **High** | Build the spine + saves in Phase 1, not late (12.4); versioned/migratable format for a long-lived project. |
| R7 | **Art coherence** — kitbash looks like a bag of mismatched assets | **Medium** | The unifying "house style": lighting, color-grade, weather, restraint (10.2). |
| R8 | **Generation quality** — procedural cases feel samey, unfair, or unsolvable | **Medium** | Solvable-by-construction grammar + case validator (9.2, 9.5); flavor layer for variety; tuning by feel (9.6). |
| R9 | **UI time-sink** — several screens *are* the gameplay and can eat months | **Medium** | Few, reusable, diegetic-first surfaces (Section 11); concentrate craft on the case board, keep the rest lean. |
| R10 | **Tonal/political risk** — a cop game makes implicit statements | **Medium** | "Keep it about the work," stated deliberately; ethics carried by consequence, not preaching (7.4); Special Victims deferred as a careful, explicit decision (6.2). |
| R11 | **Solo bus-factor / burnout** — one person, one machine, long horizon | **Medium** | Source control from day one (12.6); modular, always-playable milestones; passion-project framing; AI assistance to reduce grind (12.6). |
| R12 | **"Fun" fails to materialize** — the design reads well but doesn't play well | **High** | Phase 0 exists solely to answer this before anything is built on it; "fun is found, not planned" (3.4); ship-to-playable-early everywhere. |

**How to use this register:** it's reviewed at each phase gate (Section 13). A risk
whose mitigation is *not* actually holding up in playtest gets escalated, and the
offending scope gets cut against the pillars — not negotiated with.

## 15. Appendices

### 15.A — Reference Games Teardown

What each reference proves or teaches, and what *Rise Through The Ranks* takes vs.
improves on:

- **Police Simulator: Patrol Officers** — the procedure sandbox. *Take:* authentic
  procedural texture, the satisfaction of doing the job right. *Improve:* it has a static
  identity and no career arc — we add the evolving self (Pillars 1, 2).
- **The Precinct** — neo-noir, narrative, arcade-leaning. *Take:* mood and the appeal of
  a story-driven cop game. *Improve:* it's a fixed character in a fixed story — we make
  the story the player's own path.
- **GTA RP community** — pure emergent, player-authored identity. *Take:* the power of
  letting players *become* someone; proof of demand for the fantasy. *Improve:* it's
  structureless — we add authored progression and consequence.
- **This Is the Police** — career/moral police game from a small team. *Take:* direct
  proof that "rise-through-ranks, career-as-story" works and can be built small.
  *Note:* top-down and management-led; we deliver a similar soul in 3D and first-hand.
- **Papers, Please** — one-person, constrained-scope career/morality sim. *Take:* proof
  that radical scope constraint plus a strong loop beats sprawl.
- **L.A. Noire** — investigation, interrogation, case structure. *Take:* the case as a
  playable unit; reading people. *Note:* enormous team and budget — our version is
  systemic (Section 9), not hand-authored per case.
- **Disco Elysium** — authored beats + a detective frame on a small-ish team. *Take:*
  text-forward storytelling as a cost-effective, high-impact medium (9.4).

### 15.B — Glossary

- **The two axes** — Rank (vertical authority) and Specialization (horizontal domain);
  progression is a grid, not a line (5.1).
- **Moment / Shift / Career Loop** — the three nested gameplay loops by timescale (4.1).
- **The four beats** — Observe → Judge → Act → Consequence, the structure of every
  interaction (4.2).
- **Grade** — progression *within* a rank; the Pillar 2 engine (5.3).
- **Tier vs. title** — few expensive gameplay *tiers*; many cheap prestige *titles* (5.4).
- **The spine** — the three shared data structures (Record, Reputation, World state) every
  system reads/writes (8.8).
- **The flywheel** — the self-reinforcing cycle those structures drive (8.8).
- **The three content layers** — systemic bulk (~90%), authored anchors (~10%), emergent
  (free) (9.1).
- **Anchor beat** — a hand-authored, progression-triggered story moment (9.3).
- **House style** — the unifying lighting/color identity over kitbashed art (10.2).
- **Vertical slice** — Phase 1: the whole core proven in one district (3.1, 13).

### 15.C — Consolidated Open Questions (master list)

Pulled from every section, for deliberate resolution over time:

- **Economy scope** — light personal / command-resource-only / near-zero (8.6, 8.9).
- **Off-shift simulation** — does the world evolve while clocked off? (8.9, 12.4)
- **Camera perspective** — first vs. third person (4.6) — cascades into art, UI, tech.
- **Time structure detail** — on-shift-only vs. continuous world clock nuance (8.5).
- **Death handling** — the one unresolved consequence case (8.7).
- **Special Victims** — in or out, and with what framing (6.2).
- **City regional flavor** — Penrose Bay's finer identity and palette (7.6).
- **Traversal model** — seamless drivable city vs. district hubs + fast travel (7.6, 12.7).
- **Promotion friction** — how much process before authentic becomes chore (5.7).
- **Demotion/falling** — can rank/specialization be lost? (5.7, 8.7)
- **Command-tier grades** — define internal sub-steps for Sergeant → Chief (5.7).
- **Rate of advancement** — shifts-per-promotion pacing (5.7).
- **Reputation granularity** — single per-district trust vs. finer factions (8.9).
- **LLM-assisted flavor text** — use for case prose, with guardrails? (9.6)
- **Stylization dial & character fidelity/count** — look-dev and perf calls (10.5).
- **How many specializations / districts at 1.0** vs. post-launch (6.6, 7.6).

### 15.D — Document Changelog

- **v0.1** — Vision, pillars (4), production principles, section skeleton.
- **v0.2** — Added Pillar 5 (Authenticity); wrote Section 4 (Core Gameplay Loop).
- **v0.3** — Wrote Section 5 (Rank System, two-axis) and Section 6 (Specializations).
- **v0.4** — Wrote Section 7 (World & Setting); locked modern-day, mid-size, "about the
  work."
- **v0.4.1** — City named **Penrose Bay** (coastal/port).
- **v0.5** — Wrote Section 8 (Core Systems) and the flywheel spine.
- **v1.0** — Wrote Sections 9–15 (Content, Art/Audio, UI, Tech, Roadmap, Risk,
  Appendices). **Complete first draft.**