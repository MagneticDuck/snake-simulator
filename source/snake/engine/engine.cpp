#include "snake/engine/options.h"
#include "engine.h"

/**********************************************************************************************************************/
/* snake_engine
/**********************************************************************************************************************/

void snake_engine::init(loc player_head, dir player_movement) {
    failure = false;
    score = 0;

    this->head = player_head;
    this->movement = player_movement;
    this->tail = {};
    this->target_tail = 10;
}

void snake_engine::render(frame_i &frame) {
    frame.print(rndr_opts::game_to_screen(head),
                rndr_opts::head_char(movement));
    for (loc tail_loc : tail) {
        frame.print(rndr_opts::game_to_screen(tail_loc),
                    rndr_opts::tail_char);
    }
}

void snake_engine::handle(dir movement) {
    this->movement = movement;
}

/**********************************************************************************************************************/
/* ticking
/**********************************************************************************************************************/

const bool touching(loc head, std::vector<loc> targets) {
    for (loc target :targets) if (head == target) return true;
    return false;
}

bool snake_engine::move() {
    head += loc{movement};
    return head.clamp(game_opts::board_dims.x, game_opts::board_dims.y) || touching(head, tail);
}

void snake_engine::tick() {
    score += 0.2;

    tail.push_back(head);
    if (tail.size() > target_tail) tail.erase(tail.begin());

    if (move()) failure = true;
    if (touching(head, food)) {
        score += 20;
        target_tail++;
    }
}
