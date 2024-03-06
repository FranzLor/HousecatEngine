#pragma once

struct DamageAreaComponent {
	bool isFriendly;
	int hitPercentDamage;
	double damageDelay;
	double lastDamageTimer;

	DamageAreaComponent(bool isFriendly = false, int hitPercentDamage = 0, double damageDelay = 0.0) {
		this->isFriendly = isFriendly;
		this->hitPercentDamage = hitPercentDamage;
		this->damageDelay = damageDelay;
		this->lastDamageTimer = 0.0;
	}
};