<script setup lang="ts">
import Timer from 'easytimer.js';

const props = defineProps<{
    clock: Timer
}>()

const isRunning = ref(false)

const clockDisplay = ref({
    minutes: props.clock.getTimeValues().minutes.toString(),
    seconds: props.clock.getTimeValues().seconds.toString().padStart(2, '0'),
    tenths: '0',
})

const updateDisplay = () => {
    const time = props.clock.getTimeValues()
    clockDisplay.value = {
        minutes: time.minutes.toString(),
        seconds: time.seconds.toString().padStart(2, '0'),
        tenths: time.secondTenths.toString(),
    }
}

props.clock.addEventListener('secondTenthsUpdated', updateDisplay)
props.clock.addEventListener('started', () => isRunning.value = true)
props.clock.addEventListener('paused', () => isRunning.value = false)
</script>

<template>
    <div class="flex-none w-1/2 text-center text-[10vw]"
        :class="{
            'bg-[#e8f5e9]': isRunning,
        }"
    >
        <template v-if="clockDisplay.minutes">
            {{ clockDisplay.minutes }}<span :class="{ blinking: isRunning }">:</span>{{ clockDisplay.seconds }}
        </template>
        <template v-else>
            {{ clockDisplay.seconds }}<span class="text-red-600">.{{ clockDisplay.tenths }}</span>
        </template>
    </div>
</template>
