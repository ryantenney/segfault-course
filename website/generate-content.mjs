#!/usr/bin/env node
/**
 * Generates Starlight content pages from the course README files.
 *
 * Reads every README.md under courses/ and the root README.md,
 * strips the first H1 heading (Starlight uses frontmatter title),
 * escapes MDX-incompatible patterns (bare angle brackets, curly braces),
 * and writes .md files into src/content/docs/.
 */

import { readFileSync, writeFileSync, mkdirSync, existsSync } from 'fs';
import { join, dirname } from 'path';

const ROOT = join(dirname(new URL(import.meta.url).pathname));
const PROJECT = join(ROOT, '..');
const DOCS = join(ROOT, 'src', 'content', 'docs');

function ensureDir(dir) {
  mkdirSync(dir, { recursive: true });
}

/**
 * Escape MDX-incompatible patterns in markdown content.
 * MDX treats bare <angle> and {curly} as JSX.
 * We need to escape these when they appear outside of:
 * - Fenced code blocks (``` ... ```)
 * - Inline code (`...`)
 * - HTML comments
 * - Already valid HTML tags
 */
function escapeMdxContent(content) {
  const lines = content.split('\n');
  const result = [];
  let inCodeBlock = false;

  for (const line of lines) {
    // Track fenced code blocks
    if (/^```/.test(line)) {
      inCodeBlock = !inCodeBlock;
      result.push(line);
      continue;
    }

    if (inCodeBlock) {
      result.push(line);
      continue;
    }

    // For non-code-block lines, escape problematic patterns
    // Process the line segment by segment, skipping inline code
    let escaped = '';
    let i = 0;
    while (i < line.length) {
      // Skip inline code spans
      if (line[i] === '`') {
        const end = line.indexOf('`', i + 1);
        if (end !== -1) {
          escaped += line.slice(i, end + 1);
          i = end + 1;
          continue;
        }
      }

      // Escape bare curly braces (MDX interprets as JS expressions)
      if (line[i] === '{') {
        escaped += '\\{';
        i++;
        continue;
      }
      if (line[i] === '}') {
        escaped += '\\}';
        i++;
        continue;
      }

      // Escape angle brackets that look like JSX tags but aren't valid HTML
      // Match patterns like <repo-url>, <anything non-standard>
      if (line[i] === '<') {
        // Check if it's inside a markdown link like [text](url) — skip those
        // Check if it looks like a valid HTML tag or a known safe pattern
        const rest = line.slice(i);

        // Allow standard HTML tags, comments, and common patterns
        const htmlMatch = rest.match(/^<(\/?)(\w[\w-]*)([\s>\/])/);
        const commentMatch = rest.match(/^<!--/);

        if (commentMatch) {
          // HTML comment, pass through
          const endComment = rest.indexOf('-->');
          if (endComment !== -1) {
            escaped += rest.slice(0, endComment + 3);
            i += endComment + 3;
            continue;
          }
        }

        if (htmlMatch) {
          const tag = htmlMatch[2].toLowerCase();
          const knownHtmlTags = new Set([
            'a', 'abbr', 'b', 'blockquote', 'br', 'code', 'dd', 'del',
            'details', 'div', 'dl', 'dt', 'em', 'h1', 'h2', 'h3', 'h4',
            'h5', 'h6', 'hr', 'i', 'img', 'input', 'ins', 'kbd', 'li',
            'ol', 'p', 'pre', 'q', 's', 'small', 'span', 'strong', 'sub',
            'summary', 'sup', 'table', 'tbody', 'td', 'th', 'thead', 'tr',
            'u', 'ul', 'var', 'wbr',
          ]);
          if (knownHtmlTags.has(tag)) {
            escaped += line[i];
            i++;
            continue;
          }
        }

        // Not a standard HTML tag — escape it
        escaped += '&lt;';
        i++;
        continue;
      }

      // Escape bare > that could be confused as JSX closing
      // But only when preceded by something that looks like a tag close
      // Actually, bare > in markdown is typically blockquote, leave them alone
      // MDX handles > fine except after < tags

      escaped += line[i];
      i++;
    }

    result.push(escaped);
  }

  return result.join('\n');
}

// --- Index page (from root README) ---
{
  const readme = readFileSync(join(PROJECT, 'README.md'), 'utf-8');

  let content = readme;
  // Remove H1
  content = content.replace(/^#\s+.+\n+/, '');
  content = escapeMdxContent(content);

  const page = `---
title: "segfault-course"
description: "A crash course in modern C++ for engineers who already know how to code."
template: splash
hero:
  tagline: "52 lessons. ~400 exercises. All signal, no filler. You edit code, run tests, ship understanding."
  actions:
    - text: Start Learning
      link: /01-foundations/
      icon: right-arrow
      variant: primary
    - text: View on GitHub
      link: https://github.com/ryantenney/segfault-course
      icon: external
---

${content}`;

  ensureDir(DOCS);
  writeFileSync(join(DOCS, 'index.mdx'), page);
  console.log('Created: index.mdx');
}

// --- Course and lesson structure ---
const courses = [
  {
    dir: '01-foundations',
    title: 'Course 1: Foundations',
    description: 'The C++ Mental Model',
    lessons: [
      '01-compilation-model',
      '02-namespaces',
      '03-value-semantics',
      '04-strings',
      '05-enums',
      '06-auto-and-type-deduction',
      '07-structured-bindings',
      '08-casts',
      '09-raii',
      '10-smart-pointers',
      '11-move-semantics',
      '12-optional-variant-expected',
      '13-error-handling',
    ],
  },
  {
    dir: '02-standard-library',
    title: 'Course 2: The Standard Library',
    description: 'Containers, algorithms, and utilities you reach for daily',
    lessons: [
      '14-vector-array-span',
      '15-maps-and-sets',
      '16-iterators',
      '17-algorithms',
      '18-ranges-and-views',
      '19-lambdas',
      '20-function-and-callables',
      '21-chrono',
      '22-string-processing',
      '23-filesystem',
    ],
  },
  {
    dir: '03-types-and-generics',
    title: 'Course 3: Types and Generic Programming',
    description: 'Designing types, APIs, and writing generic code',
    lessons: [
      '24-classes-and-encapsulation',
      '25-constructors-and-initialization',
      '26-operator-overloading',
      '27-inheritance-and-polymorphism',
      '28-rule-of-zero-five',
      '29-function-templates',
      '30-class-templates',
      '31-concepts-and-constraints',
      '32-type-traits-and-constexpr',
      '33-forwarding-references',
      '34-crtp-and-mixins',
    ],
  },
  {
    dir: '04-concurrency-and-async',
    title: 'Course 4: Concurrency and Async',
    description: 'Threading, synchronization, and modern async patterns',
    lessons: [
      '35-threads-and-basic-thread-safety',
      '36-mutexes-and-locks',
      '37-condition-variables',
      '38-atomic-operations',
      '39-futures-and-async',
      '40-thread-pools',
      '41-coroutines-introduction',
      '42-async-io-patterns',
    ],
  },
  {
    dir: '05-real-world-patterns',
    title: 'Course 5: Real-World Patterns',
    description: 'Applying everything to production systems',
    lessons: [
      '43-builder-pattern',
      '44-type-safe-configuration',
      '45-middleware-and-chain-of-responsibility',
      '46-serialization-and-structured-data',
      '47-resource-pools',
      '48-observer-and-event-system',
      '49-http-request-response-modeling',
      '50-logging-and-diagnostics',
      '51-error-propagation-patterns',
      '52-capstone-mini-http-handler',
    ],
  },
];

for (const course of courses) {
  const courseDir = join(DOCS, course.dir);
  ensureDir(courseDir);

  // Course overview page
  const courseReadme = join(PROJECT, 'courses', course.dir, 'README.md');
  if (existsSync(courseReadme)) {
    let content = readFileSync(courseReadme, 'utf-8');

    // Extract H1
    const h1Match = content.match(/^#\s+(.+)$/m);
    const title = h1Match ? h1Match[1] : course.title;
    content = content.replace(/^#\s+.+\n+/, '');

    // Rewrite relative links to lesson directories
    for (const lesson of course.lessons) {
      const pattern = new RegExp(`\\]\\(${lesson}/\\)`, 'g');
      content = content.replace(pattern, `](${lesson}/)`);
    }

    content = escapeMdxContent(content);

    const yamlTitle = title.replace(/"/g, '\\"');
    const page = `---
title: "${yamlTitle}"
description: "${course.description.replace(/"/g, '\\"')}"
---

${content}`;

    writeFileSync(join(courseDir, 'index.md'), page);
    console.log(`Created: ${course.dir}/index.md`);
  }

  // Lesson pages
  for (const lesson of course.lessons) {
    const lessonReadme = join(PROJECT, 'courses', course.dir, lesson, 'README.md');
    if (!existsSync(lessonReadme)) {
      console.warn(`WARNING: Missing ${lessonReadme}`);
      continue;
    }

    let content = readFileSync(lessonReadme, 'utf-8');

    // Extract H1
    const h1Match = content.match(/^#\s+(.+)$/m);
    const title = h1Match ? h1Match[1] : lesson;
    content = content.replace(/^#\s+.+\n+/, '');

    content = escapeMdxContent(content);

    const yamlTitle = title.replace(/"/g, '\\"');

    const page = `---
title: "${yamlTitle}"
---

${content}`;

    const lessonDir = join(courseDir, lesson);
    ensureDir(lessonDir);
    writeFileSync(join(lessonDir, 'index.md'), page);
    console.log(`Created: ${course.dir}/${lesson}/index.md`);
  }
}

console.log('\nDone! All content pages generated.');
