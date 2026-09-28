# Hoard Survivor

![Unreal Engine](https://img.shields.io/badge/Unreal%20Engine-5.7-black?logo=unrealengine)
![Status](https://img.shields.io/badge/status-in%20development-orange)
![CG Spectrum](https://img.shields.io/badge/CG%20Spectrum-Game%20Programming-blueviolet)

A first-person survival game built in **C++ and Unreal Engine 5.7**.
My main portfolio project for the **Game Programming** course at **CG Spectrum**.

## About

Hordes of enemies are after the monument you're trying to extract. Hold them off with melee, ranged weapons, or towers and turrets, and build up your base as the waves grow.

## Features

- **Fight your way:** melee, ranged weapons, or towers and turrets
- **Build:** towers, upgrade stations, shops, and resource-generating buildings
- **Progress between runs:** earn resource points every run and spend them in a talent tree to unlock/empower your weapons and buildings!

## Technical Highlights

- **Data driven weapons:** every weapon is a Primary Data Asset (damage, fire rate, range, magazine size, reload time, fire mode). New weapons need no new code.
- **Composition over inheritance:** one `AHSWeapon` actor plus a swappable fire type component (beam or projectile), chosen by the data asset at runtime. The player, enemies, and towers all use the same weapon class.
- **Projectile pooling:** a World Subsystem reuses projectiles per class instead of spawning and destroying them, built to handle hundreds of projectiles per second.
- **Interface based system:** anything that implements `IHSDamageable` can be hit, so weapons never depend on specific enemy classes.
- **Custom collision channels:** projectiles pierce enemies and stop at walls using custom collision channels. Projectiles lose 35% damage for each enemy they pass through.
  
### Weapon System

```mermaid
flowchart TD
    Owner["Player / Enemy / Tower"] -->|StartFire| Weapon["AHSWeapon"]
    Data["UHSWeaponData<br/>(data asset)"] -->|stats| Weapon
    Weapon -->|Fire| Comp["UHSWeaponComponent"]
    Comp --> Beam["Beam<br/>(multi line trace)"]
    Comp --> Proj["Projectile"]
    Proj -->|SpawnProjectile| Pool["UHSProjectileSubsystem<br/>(object pool)"]
    Pool --> Bullet["AHSProjectile"]
    Beam -->|damage| Target["IHSDamageable"]
    Bullet -->|damage| Target
```

## Author

**Farzad Rayan**

[LinkedIn](https://www.linkedin.com/in/farzad-rayan/) · [Email](mailto:farzad.128.black@gmail.com)
